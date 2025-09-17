<<<<<<< Updated upstream
#include <bits/stdc++.h>
using namespace std;
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
=======
// @brief Fast Matrix Multiplication (Strassen + AVX2)
// Adapted for C++14, usable as a template
#pragma GCC optimize("Ofast,unroll-loops")
#include <immintrin.h>
#include <chrono>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// Constants & Global Buffers
// ============================================================================
const unsigned MOD = 998244353;
const int SZ = 1024;       // Must be power of 2 ≥ max dimension
const int NAIVE = 128;     // Threshold where naive kernel is used
const int s1 = 64, s3 = 32;

chrono::high_resolution_clock Clock;
int64_t modmod8 = 8ULL * MOD * MOD;

alignas(32) unsigned A[SZ * SZ], B[SZ * SZ], C[SZ * SZ];
alignas(32) unsigned TMPMAT[3][349528], *BUF = &TMPMAT[0][0];
alignas(32) uint64_t TMP[NAIVE * NAIVE];
alignas(32) __m256i tmp[8 * s1];
alignas(32) uint64_t bb[NAIVE * NAIVE], cc[NAIVE * NAIVE];

const __m256i MM8 = {modmod8, modmod8, modmod8, modmod8};
uint64_t Accum_time = 0;
int calls = 0;

// ============================================================================
// Modular Helpers
// ============================================================================
inline unsigned ua(const unsigned a, const unsigned b) {
    return min(a + b, a + b - MOD);
}
inline unsigned us(const unsigned a, const unsigned b) {
    return min(a - b, a + MOD - b);
}

// ============================================================================
// Block Operations
// ============================================================================
void add03(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = ua(a[i], a[3 * N * N + i]);
}
void extract0(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = a[i];
}
void extract3(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = a[3 * N * N + i];
}
void add23(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = ua(a[2 * N * N + i], a[3 * N * N + i]);
}
void add01(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = ua(a[i], a[N * N + i]);
}
void sub13(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = us(a[N * N + i], a[3 * N * N + i]);
}
void sub20(const unsigned *a, unsigned *res, const int N) {
    for (int i = 0; i < N * N; i++) res[i] = us(a[2 * N * N + i], a[i]);
}

// ============================================================================
// Naive Kernel with AVX2
// ============================================================================
static inline __attribute__((always_inline)) __m256i shrink(__m256i a) {
    __m256i mask = _mm256_cmpgt_epi64(a - MM8, __m256i{});
    return a - (MM8 & mask);
}

static inline __attribute__((always_inline)) void naive(const unsigned *a, const unsigned *B, unsigned *C, const int N) {
    auto tp = Clock.now();
    memset(cc, 0, N * N * sizeof(uint64_t));
    for (int i = 0; i < N * N; i++) bb[i] = B[i];
    alignas(32) __m256i *b = (__m256i *)bb, *c = (__m256i *)cc;
    calls++;

    for (int i3 = 0; i3 < N; i3 += s3) {
        for (int i1 = 0; i1 < N; i1 += s1) {
            for (int k = i1; k < i1 + s1; k++) {
                tmp[8 * (k - i1) + 0] = b[k * N / 4 + i3 / 4 + 0];
                tmp[8 * (k - i1) + 1] = b[k * N / 4 + i3 / 4 + 1];
                tmp[8 * (k - i1) + 2] = b[k * N / 4 + i3 / 4 + 2];
                tmp[8 * (k - i1) + 3] = b[k * N / 4 + i3 / 4 + 3];
                tmp[8 * (k - i1) + 4] = b[k * N / 4 + i3 / 4 + 4];
                tmp[8 * (k - i1) + 5] = b[k * N / 4 + i3 / 4 + 5];
                tmp[8 * (k - i1) + 6] = b[k * N / 4 + i3 / 4 + 6];
                tmp[8 * (k - i1) + 7] = b[k * N / 4 + i3 / 4 + 7];
            }
            for (int i = 0; i < N; i++) {
                __m256i t0 = _mm256_load_si256(c + (i * N + i3) / 4 + 0);
                __m256i t1 = _mm256_load_si256(c + (i * N + i3) / 4 + 1);
                __m256i t2 = _mm256_load_si256(c + (i * N + i3) / 4 + 2);
                __m256i t3 = _mm256_load_si256(c + (i * N + i3) / 4 + 3);
                __m256i t4 = _mm256_load_si256(c + (i * N + i3) / 4 + 4);
                __m256i t5 = _mm256_load_si256(c + (i * N + i3) / 4 + 5);
                __m256i t6 = _mm256_load_si256(c + (i * N + i3) / 4 + 6);
                __m256i t7 = _mm256_load_si256(c + (i * N + i3) / 4 + 7);
                for (int k = 0; k < s1; k++) {
                    __m256i aik = _mm256_set1_epi32(a[i * N + (k + i1)]);
                    t0 = _mm256_add_epi64(t0, _mm256_mul_epu32(aik, tmp[8 * k + 0]));
                    t1 = _mm256_add_epi64(t1, _mm256_mul_epu32(aik, tmp[8 * k + 1]));
                    t2 = _mm256_add_epi64(t2, _mm256_mul_epu32(aik, tmp[8 * k + 2]));
                    t3 = _mm256_add_epi64(t3, _mm256_mul_epu32(aik, tmp[8 * k + 3]));
                    t4 = _mm256_add_epi64(t4, _mm256_mul_epu32(aik, tmp[8 * k + 4]));
                    t5 = _mm256_add_epi64(t5, _mm256_mul_epu32(aik, tmp[8 * k + 5]));
                    t6 = _mm256_add_epi64(t6, _mm256_mul_epu32(aik, tmp[8 * k + 6]));
                    t7 = _mm256_add_epi64(t7, _mm256_mul_epu32(aik, tmp[8 * k + 7]));
                    if (k % 8 == 7) {
                        t0 = shrink(t0); t1 = shrink(t1); t2 = shrink(t2); t3 = shrink(t3);
                        t4 = shrink(t4); t5 = shrink(t5); t6 = shrink(t6); t7 = shrink(t7);
                    }
                }
                _mm256_store_si256(c + (i * N + i3) / 4 + 0, t0);
                _mm256_store_si256(c + (i * N + i3) / 4 + 1, t1);
                _mm256_store_si256(c + (i * N + i3) / 4 + 2, t2);
                _mm256_store_si256(c + (i * N + i3) / 4 + 3, t3);
                _mm256_store_si256(c + (i * N + i3) / 4 + 4, t4);
                _mm256_store_si256(c + (i * N + i3) / 4 + 5, t5);
                _mm256_store_si256(c + (i * N + i3) / 4 + 6, t6);
                _mm256_store_si256(c + (i * N + i3) / 4 + 7, t7);
            }
        }
>>>>>>> Stashed changes
    }
    for (int i = 0; i < N * N; i++) C[i] = cc[i] % MOD;
    Accum_time += chrono::duration_cast<chrono::nanoseconds>(Clock.now() - tp).count();
}

// ============================================================================
// Strassen Recursive Multiplication
// ============================================================================
void mul(const unsigned *a, const unsigned *b, unsigned *c, const int N) {
    memset(c, 0, N * N * sizeof(unsigned));
    if (N == NAIVE) { naive(a, b, c, N); return; }

    const int offset = (SZ * SZ - N * N) / 3;
    unsigned *m1 = TMPMAT[0] + offset;
    unsigned *m2 = TMPMAT[1] + offset;
    unsigned *m3 = TMPMAT[2] + offset;

    // Strassen's 7 multiplications
    add03(a, m2, N/2); add03(b, m3, N/2); mul(m2, m3, m1, N/2);
    memcpy(c, m1, N*N*sizeof(unsigned)/4); memcpy(c + 3*N*N/4, m1, N*N*sizeof(unsigned)/4);

    add23(a, m2, N/2); extract0(b, m3, N/2); mul(m2, m3, m1, N/2);
    memcpy(c + N*N/2, m1, N*N*sizeof(unsigned)/4);
    for (int i = 0; i < N*N/4; i++) c[i + 3*N*N/4] = us(c[i + 3*N*N/4], m1[i]);

    sub13(b, m3, N/2); extract0(a, m2, N/2); mul(m2, m3, m1, N/2);
    for (int i = 0; i < N*N/4; i++) c[i + N*N/4] = ua(c[i + N*N/4], m1[i]);
    for (int i = 0; i < N*N/4; i++) c[i + 3*N*N/4] = ua(c[i + 3*N*N/4], m1[i]);

    extract3(a, m2, N/2); sub20(b, m3, N/2); mul(m2, m3, m1, N/2);
    for (int i = 0; i < N*N/4; i++) c[i] = ua(c[i], m1[i]);
    for (int i = 0; i < N*N/4; i++) c[i + N*N/2] = ua(c[i + N*N/2], m1[i]);

    add01(a, m2, N/2); extract3(b, m3, N/2); mul(m2, m3, m1, N/2);
    for (int i = 0; i < N*N/4; i++) c[i] = us(c[i], m1[i]);
    for (int i = 0; i < N*N/4; i++) c[i + N*N/4] = ua(c[i + N*N/4], m1[i]);

    sub20(a, m2, N/2); add01(b, m3, N/2); mul(m2, m3, m1, N/2);
    for (int i = 0; i < N*N/4; i++) c[i + 3*N*N/4] = ua(c[i + 3*N*N/4], m1[i]);

    sub13(a, m2, N/2); add23(b, m3, N/2); mul(m2, m3, m1, N/2);
    for (int i = 0; i < N*N/4; i++) c[i] = ua(c[i], m1[i]);
}

// ============================================================================
// Prep and Reverse-Prep (quadrant mapping)
// ============================================================================
void prep(unsigned *dst, const unsigned *src, int ofs1, int ofs2, int ofs3, int N) {
    if (N == NAIVE) {
        for (int i = 0; i < NAIVE; i++)
            for (int j = 0; j < NAIVE; j++)
                dst[ofs3 + i * NAIVE + j] = src[(i + ofs1) * SZ + j + ofs2];
        return;
    }
    prep(dst, src, ofs1, ofs2, ofs3, N/2);
    prep(dst, src, ofs1, ofs2+N/2, ofs3+N*N/4, N/2);
    prep(dst, src, ofs1+N/2, ofs2, ofs3+N*N/2, N/2);
    prep(dst, src, ofs1+N/2, ofs2+N/2, ofs3+3*N*N/4, N/2);
}

void prep_reverse(unsigned *dst, const unsigned *src, int ofs1, int ofs2, int ofs3, int N) {
    if (N == NAIVE) {
        for (int i = 0; i < NAIVE; i++)
            for (int j = 0; j < NAIVE; j++)
                dst[(i + ofs1) * SZ + j + ofs2] = src[ofs3 + i * NAIVE + j];
        return;
    }
    prep_reverse(dst, src, ofs1, ofs2, ofs3, N/2);
    prep_reverse(dst, src, ofs1, ofs2+N/2, ofs3+N*N/4, N/2);
    prep_reverse(dst, src, ofs1+N/2, ofs2, ofs3+N*N/2, N/2);
    prep_reverse(dst, src, ofs1+N/2, ofs2+N/2, ofs3+3*N*N/4, N/2);
}

// ============================================================================
// Public Wrapper
// ============================================================================
vector<unsigned> multiply_matrices(const vector<unsigned> &M1, const vector<unsigned> &M2, int n, int m, int p) {
    // Load M1 into A
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            BUF[i * SZ + j] = M1[i * m + j];
    prep(A, BUF, 0, 0, 0, SZ);

    // Load M2 into B
    for (int i = 0; i < m; i++)
        for (int j = 0; j < p; j++)
            BUF[i * SZ + j] = M2[i * p + j];
    prep(B, BUF, 0, 0, 0, SZ);

    // Multiply
    mul(A, B, C, SZ);

    // Extract result
    prep_reverse(BUF, C, 0, 0, 0, SZ);
    vector<unsigned> result(n * p);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            result[i * p + j] = BUF[i * SZ + j];
    return result;
}

// ============================================================================
// Example Usage
// ============================================================================
#ifdef LOCAL_TEST
int main() {
    int n = 4, m = 4, p = 4;
    vector<unsigned> M1 = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
        13,14,15,16
    };
    vector<unsigned> M2 = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    vector<unsigned> R = multiply_matrices(M1, M2, n, m, p);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) cout << R[i * p + j] << " ";
        cout << "\n";
    }
}
<<<<<<< Updated upstream
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> par(n, -1);
        vt<vt<int>> chil(n);
        FOR(i, 1, n) {
            cin >> par[i];
            --par[i];
            chil[par[i]].add(i);
        }
        vt<int> depth(n);
        auto dfs = [&](auto self, int node)->void{
            trav(x, chil[node]) {
                depth[x]=depth[node]+1;
                self(self, x);
            }
        };
        dfs(dfs,0);
        int largest = n;
        F0R(i, n) if(chil[i].size()==0) largest=min(largest, depth[i]);
        vt<int> number(n+1);
        F0R(i, n) number[depth[i]]++;
        vt<vt<bool>> dp(n+1, vt<bool>(n+1));
        if(k!=0) dp[0][k-1]=true;
        if(k!=n) dp[0][n-k-1]=true;
        int left = n-1;
        int ans = 0;
        // assert(false);
        F0R(i, largest+1) {
            F0R(j, n) {
                if(dp[i][j]) {
                    cout << i << " " << j << endl;
                    ans=i+1;
                    int other = left-j;
                    if(j>=number[i+1]) {
                        dp[i+1][j-number[i+1]]=true;
                    }
                    if(other>=number[i+1]) {
                        dp[i+1][other-number[i+1]]=true;
                    }
                }
            }
            left-=number[i+1];
        }
        cout << ans << endl;
    }
    return 0;
}
=======
#endif
>>>>>>> Stashed changes
