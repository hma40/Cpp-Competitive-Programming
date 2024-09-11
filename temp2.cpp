#include <bits/stdc++.h>
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
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rand_num(int l, int h) {
    return rnd()%(h-l+1)+l;
}
struct TestCase {
    int n;
    vt<int> a;
};
void fill_rand(vt<int> &v, int lo, int hi) {
    for(auto &x: v) {
        x=rnd()%(hi-lo+1)+lo;
    }
}
void rand_tree(vt<vt<int>> &adj) {
    for(int i = 1; i < adj.size(); i++) {
        int par = rnd()%i;
        adj[par].add(i);
        adj[i].add(par);
    }
}
void print_TC(TestCase tc) {
    cout << tc.n << endl << tc.a << endl;
}
TestCase randTC() {
    TestCase tc;    
    tc.n=50;
    F0R(i, tc.n) {
        tc.a.add(rand_num(-25,25));
    }
    return tc;
}
struct WrongSol {
    int solve(TestCase tc) {
        vt<int> pow2 = {1,2,4,8,16,32,64,128,256,512,1024,2048};
        int n=tc.n;
        // cin >> n;
        vt<int> a=tc.a;
        // F0R(i, n) cin >> a[i];
        vt<int> pref(n+1);
        F0R(i, n) pref[i+1]=pref[i]+a[i];
        int mx = 0;
        FOR(i, 1, n+1) {
            //assume abs val used before a[i]
            mx=max(mx, abs(pref[i])+pref[n]-pref[i]);
        }
        int ans = 0;
        vt<int> critVal(n+1),ways(n+1);
        critVal[0]=mx-pref[n];
        if(critVal[0]==0) ways[0]=1;
        int nonneg = 0;
        FOR(i, 1, n+1) {
            critVal[i]=mx-pref[n]+pref[i];
            ways[i]=ways[i-1]*2;
            if(pref[i]<0&&abs(pref[i])==critVal[i]) {
                ways[i]+=pow2[nonneg];
            }
            if(pref[i]>=0) nonneg++;
        }
        return ways.back();
    }
};
struct CorrectSol {
    int solve(TestCase tc) {
        vt<int> p2 = {1,2,4,8,16,32,64,128,256,512,1024,2048};
        int n=tc.n;
        vector<int> arr=tc.a;// for (int i = 0; i < n; ++i) cin >> arr[i];
        ll sum = 0, mn = 0, ans = 0, abses = 0;
        for (int i = 0; i < n; ++i) sum += arr[i], mn = min(mn, sum);
        if (mn == 0) {
            // cout << p2[n] << '\n';
            return p2[n];
        }
        sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += arr[i];
            if (sum == mn) {
            ans = (ans + p2[n - i - 1 + abses]) % mod;
            }
            if (sum >= 0) ++abses;
        }
        // cout << ans << '\n';
        return ans;
    }
};
signed main() {
    while(true) {
        TestCase tc = randTC();
        WrongSol w;
        CorrectSol c;
        auto wa = w.solve(tc);
        auto cor = c.solve(tc);
        if(wa==cor) {
            cout << "PASSED" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
        } else {
            cout << "WRONG ANSWER" << endl;
            print_TC(tc);
            cout << wa << endl << cor << endl;
            break;
        }
    }
    return 0;
}