#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define vb vector<bool>
#define vs vector<string>
#define all(x) (x).begin(), (x).end()
#define umap unordered_map
#define uset unordered_set
#define sz(x) (int((x).size()))
#define elif else if
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define int long long
#define X real()
#define Y imag()
using namespace __gnu_pbds;

#define cross_product(a, b) ((conj((a)) * (b)).imag())
#define dot_product(a, b) ((conj((a)) * (b)).real())

namespace modular
{
    const int MOD = 1'000'000'007;
    const int PHI = MOD - 1; // for primes
    struct mint
    {
        int v;
        mint() : v(0) {}
        mint(int a)
        {
            if (a < 0)
                v = ((a % MOD) + MOD) % MOD;
            else if (a < MOD)
                v = a;
            else
                v = a % MOD;
        }
        mint sqr() { return (*this) * (*this); }
        mint inv() { return (*this) ^ (PHI - 1); }
        friend mint operator+(mint a, mint b) { return {(a.v + b.v) % MOD}; }
        friend mint operator-(mint a, mint b) { return {(a.v + MOD - b.v) % MOD}; }
        friend mint operator*(mint a, mint b) { return {(long long)((1LL * a.v * b.v) % MOD)}; }
        friend mint operator/(mint a, mint b) { return a * b.inv(); }
        friend mint operator^(mint a, int b) { return b == 0 ? 1 : b == 1 ? a
                                                               : b % 2    ? a * (a ^ (b - 1))
                                                                          : (a ^ (b / 2)).sqr(); }
        friend bool operator==(mint a, mint b) { return a.v == b.v; }
        friend bool operator!=(mint a, mint b) { return a.v != b.v; }
        friend mint operator+=(mint &a, mint b) { return a = a + b; }
        friend mint operator-=(mint &a, mint b) { return a = a - b; }
        friend mint operator*=(mint &a, mint b) { return a = a * b; }
        friend mint operator/=(mint &a, mint b) { return a = a / b; }
        friend mint operator^=(mint &a, int b) { return a = a ^ b; }
        friend ostream &operator<<(ostream &stream, const mint &a)
        {
            stream << a.v;
            return stream;
        }
    };
    vector<mint> F = {1}, IF = {1};
    mint tri(mint a) { return a * (a + 1) / 2; }
    mint rng(mint a, mint b) { return tri(b) - tri(a - 1); }
    mint fact(int a)
    {
        while (a >= (int)F.size())
            F.push_back(F.back() * F.size());
        return a >= 0 ? F[a] : 0;
    }
    mint invfact(int a)
    {
        while (a >= (int)IF.size())
            IF.push_back(IF.back() / IF.size());
        return a >= 0 ? IF[a] : throw("bad");
    }
    mint nCr(int n, int k) { return n >= k ? fact(n) * invfact(k) * invfact(n - k) : 0; }
    mint nPr(int n, int k) { return n >= k ? fact(n) * invfact(n - k) : 0; }
    mint pmink(int p, int m, int k) { return k > p - m ? 0 : nCr(p + m, p) - nCr(p + m, m + k - 1); }
    mint pmaxk(int p, int m, int k) { return k < p - m ? 0 : nCr(p + m, p) - nCr(p + m, p - k - 1); }
    mint large_nCr(int n, int k)
    {
        mint res = 1;
        int m = min(k, n - k);
        if (m == 0)
            return 1;
        if (m < 0)
            return 0;
        for (int i = 1; i <= m; i++)
            res *= mint(n - m + i) / i;
        return res;
    }
};

using namespace modular;

struct Lagrange
{
    vector<mint> C;
    // lagrangian interpolation in O(deg^2)
    Lagrange(vector<ll> X, vector<ll> Y)
    {
        int n = X.size();
        C.resize(n);
        vector<mint> _all(n + 1);
        _all[0] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = n; j >= 0; j--)
            {
                _all[j] *= (-X[i]);
                if (j)
                    _all[j] += _all[j - 1];
            }
        }
        for (int i = 0; i < n; i++)
        {
            // all / (x-x{i})
            vector<mint> top(n);
            mint curr = 1;
            for (int j = n - 1; j >= 0; j--)
            {
                top[j] = curr;
                curr = _all[j] + curr * X[i];
            }
            // (x{i}-x0)/(x{i}-x1)/.../(x{i}-x{n-1}) [skipping (x{i}-x{i})]
            mint down = 1;
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;
                down *= (X[i] - X[j]);
            }
            // add into the answer
            for (int j = 0; j < n; j++)
            {
                C[j] += Y[i] * top[j] / down;
            }
        }
    }
    // evaluate in O(deg)
    mint evaluate(ll x)
    {
        mint curr = 1, ans = 0;
        for (mint c : C)
        {
            ans += c * curr;
            curr *= x;
        }
        return ans;
    }
};

const int alpha = 26; // alphabet size
random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> dist(alpha, PHI);
int p = dist(mt);

// range max
struct Info
{
    ll m;
    Info(ll _m) : m(_m) {}
    Info() : m(0) {}
    Info combine(Info &other) { return {max(m, other.m)}; }
};

struct Tree
{
    vector<Info> info;
    int size;
    Tree(int sz)
    {
        this->size = sz;
        info.resize(sz * 4);
    }
    void build(vector<Info> &base, int x, int xl, int xr)
    {
        if (xl == xr)
        {
            info[x] = base[xl];
        }
        else
        {
            int xm = (xl + xr) / 2;
            build(base, x * 2, xl, xm);
            build(base, x * 2 + 1, xm + 1, xr);
            info[x] = info[x * 2].combine(info[x * 2 + 1]);
        }
    }
    void update(int v, Info val, int x, int xl, int xr)
    {
        if (xl == xr)
        {
            info[x] = val;
        }
        else
        {
            int xm = (xl + xr) / 2;
            if (v <= xm)
                update(v, val, x * 2, xl, xm);
            else
                update(v, val, x * 2 + 1, xm + 1, xr);
            info[x] = info[x * 2].combine(info[x * 2 + 1]);
        }
    }
    void update(int v, Info val)
    {
        update(v, val, 1, 0, size - 1);
    }
    Info query(int l, int r, int x, int xl, int xr)
    {
        if (l > r)
            return {};
        if (l == xl && r == xr)
        {
            return info[x];
        }
        else
        {
            int xm = (xl + xr) / 2;
            Info left = query(l, min(r, xm), x * 2, xl, xm);
            Info right = query(max(l, xm + 1), r, x * 2 + 1, xm + 1, xr);
            return left.combine(right);
        }
    }
    Info query(int l, int r)
    {
        return query(l, r, 1, 0, size - 1);
    }
    int find_first(function<bool(Info &)> pred, int x, int xl, int xr)
    {
        if (xl == xr)
        {
            if (pred(info[x]))
                return xl;
            else
                return -1;
        }
        else
        {
            int xm = (xl + xr) / 2;
            if (pred(info[x * 2]))
                return find_first(pred, x * 2, xl, xm);
            else
                return find_first(pred, x * 2 + 1, xm + 1, xr);
        }
    }
    int find_first(function<bool(Info &)> pred)
    {
        return find_first(pred, 1, 0, size - 1);
    }
};

struct StringHash
{
    vector<mint> pre;
    vector<mint> inv;
    StringHash(string s)
    {
        int n = s.size();
        pre.resize(n + 1);
        pre[0] = 0;
        mint curr = 1;
        for (int i = 0; i < n; i++)
        {
            pre[i + 1] = pre[i] + ((s[i] - 'a') * curr);
            curr *= p;
        }
        inv.resize(n, 1);
        if (n > 1)
        {
            inv[1] /= p;
            for (int i = 2; i < n; i++)
            {
                inv[i] = inv[i - 1] * inv[1];
            }
        }
    }
    StringHash() : StringHash("") {}
    mint query(int l, int r)
    {
        mint ans = pre[r + 1] - pre[l];
        return ans * inv[l];
    }
};

struct IsOfFormAB
{
    vector<vi> odd;
    vector<vi> even;
    IsOfFormAB(string s)
    {
        even.resize(s.size() + 1, vi(26, 0));
        odd.resize(s.size() + 1, vi(26, 0));
        for (int i = 0; i < s.size(); i++)
        {
            for (int j = 0; j < 26; j++)
            {
                even[i + 1][j] = even[i][j];
                odd[i + 1][j] = odd[i][j];
                if (s[i] == 'a' + j)
                {
                    if (i % 2 == 0)
                    {
                        even[i + 1][j]++;
                    }
                    else
                    {
                        odd[i + 1][j]++;
                    }
                }
            }
        }
    }
    int query(int l, int r)
    {
        vi odd_diff(26, 0);
        vi even_diff(26, 0);
        for (int i = 0; i < 26; i++)
        {
            odd_diff[i] = odd[r + 1][i] - odd[l][i];
            even_diff[i] = even[r + 1][i] - even[l][i];
        }

        int prev = -1;
        for (int i = 0; i < 26; i++)
        {
            if (odd_diff[i] != 0)
            {
                if (prev != -1)
                {
                    return 0;
                }
                prev = i;
            }
        }

        int prev2 = -1;
        for (int i = 0; i < 26; i++)
        {
            if (even_diff[i] != 0)
            {
                if (prev2 != -1)
                {
                    return 0;
                }
                prev2 = i;
            }
        }

        if (prev == prev2)
            return 2; // of form aaaaaaa
        return 1;     // of form abababab
    }
};

struct Palindromes
{
    StringHash forward, backward;
    int n;
    Palindromes(string s)
    {
        forward = StringHash(s);
        reverse(s.begin(), s.end());
        backward = StringHash(s);
        n = s.size();
    }
    bool query(int l, int r)
    {
        mint f = forward.query(l, r);
        mint b = backward.query(n - 1 - r, n - 1 - l);
        return (f == b);
    }
};

class DisjointSets
{
public:
    vector<int> parents;
    vector<int> sizes;
    DisjointSets(int size) : parents(size), sizes(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parents[i] = i;
        }
    }
    int find(int x)
    {
        return parents[x] == x ? x : (parents[x] = find(parents[x]));
    }
    bool unite(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root)
        {
            return false;
        }
        if (sizes[x_root] < sizes[y_root])
        {
            swap(x_root, y_root);
        }
        sizes[x_root] += sizes[y_root];
        parents[y_root] = x_root;
        return true;
    }
    bool connected(int x, int y) { return find(x) == find(y); }
};

class IntervalSet
{
public:
    std::set<std::pair<int, int>> intervals;
    void addInterval(int l, int r)
    {
        auto it = intervals.lower_bound({l, r});

        if (it != intervals.begin())
        {
            auto prev = std::prev(it);
            if (prev->second >= l)
            {
                l = std::min(l, prev->first);
                r = std::max(r, prev->second);
                intervals.erase(prev);
            }
        }

        while (it != intervals.end() && it->first <= r)
        {
            l = std::min(l, it->first);
            r = std::max(r, it->second);
            it = intervals.erase(it);
        }

        intervals.insert({l, r});
    }

    void printIntervals() const
    {
        for (const auto &interval : intervals)
        {
            std::cout << "[" << interval.first << ", " << interval.second << "] ";
        }
        std::cout << std::endl;
    }
};

vector<complex<int>> conv_hull(vector<complex<int>> points)
{
    sort(points.begin(), points.end(), [](complex<int> a, complex<int> b)
         { return a.real() < b.real() || (a.real() == b.real() && a.imag() < b.imag()); });
    vector<complex<int>> hull;
    for (int i = 0; i < 2; i++)
    {
        int start = hull.size();
        for (auto point : points)
        {
            while (hull.size() >= start + 2 && cross_product(hull[hull.size() - 1] - hull[hull.size() - 2], point - hull[hull.size() - 2]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(points.begin(), points.end());
    }
    return hull;
}

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T, typename T2>
auto operator<<(std::ostream &os, const std::pair<T, T2> &p) -> std::ostream &
{
    os << '(';
    if (typeid(T) == typeid(string))
    {
        os << '"' << p.first << '"';
    }
    else
    {
        os << p.first;
    }
    os << ", ";
    if (typeid(T2) == typeid(string))
    {
        os << '"' << p.second << '"';
    }
    else
    {
        os << p.second;
    }
    os << ')';
    return os;
}

template <typename T>
auto operator<<(std::ostream &os, const std::vector<T> &v) -> std::ostream &
{
    os << "[";
    if (v.size() == 0)
    {
        os << "]";
        return os;
    }
    if (typeid(T) == typeid(string))
    {
        os << '"' << v[0] << '"';
    }
    else
    {
        os << v[0];
    }
    for (int i = 1; i < v.size(); i++)
    {
        if (typeid(T) == typeid(string))
        {
            os << ", " << '"' << v[i] << '"';
        }
        else
        {
            os << ", " << v[i];
        }
    }
    os << "]";
    return os;
}

template <typename T>
auto operator<<(std::ostream &os, const std::set<T> &s) -> std::ostream &
{
    if (s.size() == 0)
    {
        os << "{}";
        return os;
    }
    os << "{";

    int i = 0;

    for (auto value : s)
    {
        if (i++ != 0)
            os << ", ";
        if (typeid(T) == typeid(string))
            os << '"' << value << '"';
        else
            os << value;
    }
    os << "}";
    return os;
}

template <typename T>
auto operator<<(std::ostream &os, const std::unordered_set<T> &s) -> std::ostream &
{
    if (s.size() == 0)
    {
        os << "{}";
        return os;
    }
    os << "{";

    int i = 0;

    for (auto value : s)
    {
        if (i++ != 0)
            os << ", ";
        if (typeid(T) == typeid(string))
            os << '"' << value << '"';
        else
            os << value;
    }
    os << "}";
    return os;
}

template <typename T, typename T2>
auto operator<<(std::ostream &os, const std::map<T, T2> &m) -> std::ostream &
{
    if (m.size() == 0)
    {
        os << "{}";
        return os;
    }
    os << "{";

    int i = 0;

    for (auto [key, value] : m)
    {
        if (i++ != 0)
            os << ", ";
        if (typeid(T) == typeid(string))
            os << '"' << key << '"';
        else
            os << key;
        os << ": ";
        if (typeid(T2) == typeid(string))
            os << '"' << value << '"';
        else
            os << value;
    }
    os << "}";
    return os;
}

template <typename T, typename T2>
auto operator<<(std::ostream &os, const std::unordered_map<T, T2> &m) -> std::ostream &
{
    if (m.size() == 0)
    {
        os << "{}";
        return os;
    }
    os << "{";

    int i = 0;

    for (auto [key, value] : m)
    {
        if (i++ != 0)
            os << ", ";
        if (typeid(T) == typeid(string))
            os << '"' << key << '"';
        else
            os << key;
        os << ": ";
        if (typeid(T2) == typeid(string))
            os << '"' << value << '"';
        else
            os << value;
    }
    os << "}";
    return os;
}

vpii intervalise(string s) {
    vpii intervals;
    int n = s.size();
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i-1]) {
            intervals.pb({l, i-l});
            l = i;
        }
    }
    intervals.pb({l, n-l});
    return intervals;
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout << "OK" << endl;
    return 0;
    
    int ttt;
    cin >> ttt;
    nexttc:
    while (ttt--) {
        string s1, s2;
        cin >> s1 >> s2;
        if (s1[0] != s2[0]) {
            cout << "NO" << endl;
        }
        vpii intervals1 = intervalise(s1);
        vpii intervals2 = intervalise(s2);
        if (intervals1.size() != intervals2.size()) {
            cout << "NO" << endl;
            continue;
        }

        for (int i = 0; i < intervals1.size(); i++) {
            if (intervals2[i].second > 2 * intervals1[i].second) {
                cout << "NO" << endl;
                goto nexttc;
            }
            else if (intervals2[i].second < intervals1[i].second) {
                cout << "NO" << endl;
                goto nexttc;
            }
        }

        cout << "YES" << endl;
    }

    return 0;
}