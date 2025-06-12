#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> std::ostream& operator<<(std::ostream& os, min_pq<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
using namespace std;
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
const ll MOD = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%MOD;
        b=b*b%MOD;
        e>>=1;
    }
    return ans;
}
// Fast modular exponentiation.
int modExp(int base, int exp) {
    long long result = 1, b = base;
    while(exp > 0) {
        if(exp & 1)
            result = (result * b) % MOD;
        b = (b * b) % MOD;
        exp >>= 1;
    }
    return (int)result;
}
 
// Modular inverse using Fermat’s little theorem.
int modInv(int a) {
    return modExp(a, MOD - 2);
}
 
// Naïve polynomial multiplication (convolution) in O(degA*degB).
// Given two polynomials A and B (represented as coefficient vectors, where
// A[i] is the coefficient of x^i), returns their product modulo MOD.
vector<int> polyMult(const vector<int> &A, const vector<int> &B) {
    int n = A.size(), m = B.size();
    vector<int> C(n + m - 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i+j] = (C[i+j] + (long long) A[i] * B[j]) % MOD;
        }
    }
    return C;
}
 
// Build the product polynomial Q(x) = (x- l) * (x- (l+1)) * ... * (x- r)
// using divide & conquer. (This runs in O((r-l+1)*log(r-l+1)*polyMultCost).)
vector<int> buildPoly(int l, int r) {
    if(l > r) return {1};
    if(l == r) {
        // return polynomial (x - l)
        int coeff = (MOD - (l % MOD)) % MOD;
        return {coeff, 1};
    }
    int mid = (l + r) / 2;
    vector<int> leftPoly = buildPoly(l, mid);
    vector<int> rightPoly = buildPoly(mid+1, r);
    return polyMult(leftPoly, rightPoly);
}
 
// Given a polynomial poly, compute its derivative.
// poly represents ∑ poly[i]*x^i. The derivative is ∑ i*poly[i]*x^(i-1).
vector<int> polyDerivative(const vector<int> &poly) {
    int n = poly.size();
    if(n == 0) return {};
    vector<int> deriv;
    for (int i = 1; i < n; i++) {
        deriv.push_back((int)((long long)i * poly[i] % MOD));
    }
    return deriv;
}
 
// Horner's method to evaluate a polynomial at a given point x.
int evaluatePoly(const vector<int> &poly, int x) {
    long long result = 0;
    for (int i = poly.size()-1; i >= 0; i--) {
        result = (result * x + poly[i]) % MOD;
    }
    return (int)result;
}
 
// interpolate computes the unique polynomial P(x) of degree n-1 such that
// P(i) = points[i] for i = 0, 1, …, n-1. (points has length n+1,
// so if the values come from a degree n-1 polynomial then points[n] is consistent.)
// The algorithm runs in O(n log(mod)) provided that polyMult is replaced by an
// NTT-based multiplication routine. (For simplicity here we use a naïve O(n^2) mult.)
vector<int> interpolate(vector<int> &points) {
    int totalPoints = points.size();
    // Since the polynomial is of degree n-1, we use the first n points.
    int n = totalPoints - 1;
    // Build A(x) = ∏₍ᵢ₌₀₎ⁿ⁻¹ (x - i)
    vector<int> A = buildPoly(0, n - 1);  // degree = n
    // Compute A'(x) (the derivative of A)
    vector<int> A_deriv = polyDerivative(A);
    // For each i in 0,1,...,n-1, compute denom = A'(i) and take its modular inverse.
    vector<int> invDenom(n, 0);
    for (int i = 0; i < n; i++) {
        int val = evaluatePoly(A_deriv, i);
        invDenom[i] = modInv(val);
    }
 
    // Precompute the “prefix” and “suffix” arrays.
    // prefix[i] = ∏₍₀ ≤ j < i₎ (x - j)
    // suffix[i] = ∏₍ᵢ ≤ j < n₎ (x - j)
    vector<vector<int>> prefix(n + 1), suffix(n + 1);
    prefix[0] = {1};
    for (int i = 0; i < n; i++){
        vector<int> factor = { (MOD - i) % MOD, 1 }; // (x - i)
        prefix[i+1] = polyMult(prefix[i], factor);
    }
    suffix[n] = {1};
    for (int i = n - 1; i >= 0; i--){
        vector<int> factor = { (MOD - i) % MOD, 1 };
        suffix[i] = polyMult(factor, suffix[i+1]);
    }
 
    // Now compute the interpolated polynomial P(x) defined by:
    // P(x) = ∑₍ᵢ₌₀₎ⁿ⁻¹ points[i] * invDenom[i] * (prefix[i] * suffix[i+1])
    // Notice that (prefix[i] * suffix[i+1]) equals A(x)/(x - i) and is a degree n-1 polynomial.
    vector<int> result(n, 0);  // degree n-1: n coefficients from constant term up
    for (int i = 0; i < n; i++){
        vector<int> term = polyMult(prefix[i], suffix[i+1]); // degree n-1
        long long coeff = (long long) points[i] * invDenom[i] % MOD;
        // Add this term into the result.
        for (int j = 0; j < term.size(); j++){
            result[j] = (result[j] + (long long) coeff * term[j]) % MOD;
        }
    }
    return result;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int n,k;
    cin >> n >> k;
    vt<int> points(k+1);
    FOR(i, 1, k+1) points[i]=(points[i-1]+bexpo(i, k))%MOD;
    cout << points << endl;
    // return 0;
    auto x = interpolate(points);
    // return 0;
    cout << x << endl;
    int ans = 0;
    for(int i = 0; i < x.size(); i++) {
        ans+=bexpo(n, i)*x[i]%MOD;
        ans%=MOD;
    }
    cout << ans << endl;
    return 0;
}