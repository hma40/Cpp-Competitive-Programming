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
        q.pop_front();
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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
FastMod fs(mod);
set<int> bad;
vt<int> a, inv;
int test(pair<int,int> fuck) {
    int x = fuck.f, y = fuck.s;
    int ans = 0;
    swap(a[x], a[y]);
    if(a[x]==x) {
        ans++;
    } else if(a[a[x]]==x) {
        ans+=2;
    }
    if(a[y]==y) {
        ans++;
    } else if(a[a[y]]==y) {
        ans+=2;
    }
    swap(a[x], a[y]);
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        bad.clear();
        a.resize(n);
        inv.resize(n);
        F0R(i, n) cin >> a[i];

        F0R(i, n) {
            a[i]--;
            bad.insert(i);
        }
        F0R(i, n) {
            if(!bad.count(i)) continue;
            if(a[i]==i||a[a[i]]==i) {
                bad.erase(i);
                bad.erase(a[a[i]]);
            }
        }
        /*
        greedily choose:
        - set a[i] = i
        - set a[a[j]]=i
        - set a[i] = inva[i]
        */
        int ans = 0;
        F0R(i, n) inv[a[i]]=i;
        F0R(i, n) {
            if(!bad.count(i)) continue;
            vt<pair<int,int>> choices;
            choices.add({i, inv[i]});
            choices.add({i, inv[inv[i]]});
            choices.add({inv[i], a[i]});
            auto xx = test(choices[0]);
            auto yy =test(choices[1]);
            auto zz = test(choices[2]);
            ans++;
            // cout << xx << " " << yy << " " << zz << choices << endl;
            if(xx>=yy&&xx>=zz) {
                // cout << "LINE 216" << endl;
                swap(a[i], a[inv[i]]);
                int x = i, y = inv[i];
                inv[a[x]]=x;
                inv[a[y]]=y;
                if(a[a[x]]==x) {
                    bad.erase(x);
                    bad.erase(a[x]);
                }
                if(a[a[y]]==y) {
                    bad.erase(y);
                    bad.erase(a[y]);
                }
            } else if(yy>=xx&&yy>=zz) {
                swap(a[i], a[inv[inv[i]]]);
                int x = i, y = inv[inv[i]];
                inv[a[x]]=x;
                inv[a[y]]=y;
                if(a[a[x]]==x) {
                    bad.erase(x);
                    bad.erase(a[x]);
                }
                if(a[a[y]]==y) {
                    bad.erase(y);
                    bad.erase(a[y]);
                }
            } else {
                swap(a[inv[i]], a[a[i]]);
                int x = inv[i], y = a[i];
                inv[a[x]]=x;
                inv[a[y]]=y;
                if(a[a[x]]==x) {
                    bad.erase(x);
                    bad.erase(a[x]);
                }
                if(a[a[y]]==y) {
                    bad.erase(y);
                    bad.erase(a[y]);
                }
            }
            // cout << a << bad << inv << endl;   
        }
        cout << ans << endl;
    }
    return 0;
}
/*
4 2 3 1 0
4 1 3 2 0
*/