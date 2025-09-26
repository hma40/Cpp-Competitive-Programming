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
#define double long double
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e) {
    int a = 1;
    while(e) {
        if(e&1) a=a*b%mod;
        e>>=1;
        b=b*b%mod;
    }
    return a;
}
vt<int> fact(200005), invfact(200005);
int nck(int n, int k) {
    return fact[n]*invfact[k]%mod*invfact[n-k]%mod;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fact[0]=invfact[0]=1;
    FOR(i, 1, 200005) fact[i]=fact[i-1]*i%mod;
    F0R(i, 200005) {
        invfact[i]=bexpo(fact[i], mod-2);
    }
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q;
        cin >> n >> q;
        vt<int> pref(n+2), oddPref(n+2), evenPref(n+2), oddSuff(n+2), evenSuff(n+2), suff(n+2);
        F0R(i, n+1) {
            pref[i+1]=pref[i]+nck(n,i);
            oddPref[i+1]=oddPref[i];
            evenPref[i+1]=evenPref[i];
            if(i%2) oddPref[i+1]+=pref[i+1];
            else evenPref[i+1]+=pref[i+1];
            pref[i+1]%=mod;
            oddPref[i+1]%=mod;
            evenPref[i+1]%=mod;
        }
        // cout << pref << endl << oddPref << endl << evenPref << endl;
        string s;
        cin >> s;
        int zc = 0, oc = 0;
        F0R(i, n) if(s[i]=='0') zc++; else oc++;
        int ans = 0;
        int nxt = 0;
        FOR(i, -zc, oc+1) {
            int score = (abs(i)/2)*((abs(i)+1)/2)%mod;
            ans+=nck(n, i+zc)*score;
            ans%=mod;
        }
        // cout << ans << endl;
        while(q--) {
            int x;
            cin >> x;
            x--;
            // cout << oc << " " << zc << endl;
            if(s[x]=='0') {
                s[x]='1';
                if(zc%2) {
                    ans-=oddPref[zc-1];
                } else if(zc!=0) {
                    ans-=evenPref[zc-1];
                }
                if(oc%2) {
                    ans+=evenPref[oc];
                } else {
                    ans+=oddPref[oc];
                }
                ans%=mod;
                ans+=mod;
                ans%=mod;
                zc--;
                oc++;
            } else {
                s[x]='0';
                if(oc%2) {
                    ans-=oddPref[oc-1];
                } else if(oc!=0) {
                    ans-=evenPref[oc-1];
                }
                if(zc%2) {
                    ans+=evenPref[zc];
                } else {
                    ans+=oddPref[zc];
                }
                ans%=mod;
                ans+=mod;
                ans%=mod;
                zc++;
                oc--;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
/*
6 zeroes 9 ones -> 7 zeroes 8 ones
(15c0)(3)(3)    (15c1)(3)(3-1)   (15c2)(2)(2)
(15c0)(3)(3+1)  (15c1)(3)(3)     (15c2)(2)(2+1)
(15c0)(3)       (15c1)(3)        (15c2)(2)             (15c3)(2)          (15c4)(1)          (15c5)(1)
+: pref(5)+pref(3)+pref(1) = oddPref(6)
(15c0)(4)(4+1)   (15c1)(4)(4)
(15c0)(4)(4)     (15c1)(4)(4-1)
(15c0)(-4)       (15c1)(-4)
-: pref(7)-pref(5)-pref(3)-pref(1) = oddPref(8)

7 zeroes 8 ones -> 8 zeroes 7 ones
(15c0)(4)(4-1)     (15c1)(3)(3)
(15c0)(4)(4)       (15c1)(3)(3+1)
(15c0)(4)          (15c1)(3) 

(15c0)(4)(4)    (15c1)(3)(3+1)
(15c0)(4)(4-1)  (15c1)(3)(3)

+ pref(6)+pref(4)+pref(2)+pref(0) = evenPref(7)
-: pref(6)+pref(4)+pref(2)+pref(0) = evenPref(7)

2 zeroes 1 one -> 1 zero 2 ones
(3c0)(1)(1)
(3c0)(1)(1-1)
+: evenPref(1)
-: evenPref(1)
*/