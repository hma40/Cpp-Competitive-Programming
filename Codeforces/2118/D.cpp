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
        int n,m,k;
        cin >> n >> m >> k;
        vt<pair<int,int>> v(m);
        F0R(i, m) cin >> v[i].f;
        F0R(i, m) cin >> v[i].s;
        sort(begin(v),end(v));
        vt<bool> badLeft(m), badRight(m);
        vt<int> rtlNext(m, -1), ltrNext(m, -1);
        //right
        map<int,int> mp;
        F0R(i, m) {
            /*
            When you go R->L at time v[i].s, position v[i].f
            at position v[i].f-1 at time v[i].s+1
            so position + time = v[i].f+v[i].s
            have to find some red light before it at position v[x].f 
            time will be v[i].f+v[i].s-v[x].f and should be equal to v[x].s mod k
            or v[i].f+v[i].s=v[x].f+v[x].s mod k
            */
            int sum = v[i].f+v[i].s;
            if(mp.count(sum%k)) {
                rtlNext[i] = mp[sum%k];
            }
            mp[sum%k]=i;
        }
        map<int,int> mp2;
        R0F(i, m) {
            /*
            at time v[i].s, pos v[i].f
            time v[i].s+1, pos v[i].f+1
            so v[i].s-v[i].f should be same as another
            */
            int diff = (v[i].s-v[i].f)%k+k;
            diff%=k;
            if(mp2.count(diff)) ltrNext[i]=mp2[diff];
            mp2[diff]=i;
        }
        vt<bool> visltr(m), visrtl(m), stuckltr(m), stuckrtl(m);
        F0R(i, m) {
            if(visltr[i]) continue;
            vt<pair<int,int>> here;
            set<pair<int,int>> added;
            here.push_back({i, 0});
            bool bad = false;
            while(true) {
                auto bk = here.back();
                if(added.count(bk)) {
                    bad=true;
                    break;
                }
                added.insert(bk);
                if(bk.s==0) {
                    if(visltr[bk.f]) {
                        if(stuckltr[bk.f]) {
                            bad=true;
                            break;
                        } else {
                            break;
                        }
                    }
                    visltr[bk.f]=true;
                    if(ltrNext[bk.f]==-1) {
                        break;
                    } else {
                        here.push_back({ltrNext[bk.f], 1});
                    }
                } else {
                    if(visrtl[bk.f]) {
                        if(stuckrtl[bk.f]) {
                            bad=true;
                            break;
                        } else {
                            break;
                        }
                    }
                    visrtl[bk.f]=true;
                    if(rtlNext[bk.f]==-1) {
                        break;
                    } else {
                        here.push_back({rtlNext[bk.f], 0});
                    }
                }
            }
            // cout << i << here << bad << endl;
            if(bad) {
                trav(x, here) {
                    if(x.s==1) {
                        stuckrtl[x.f]=true;
                    } else {
                        stuckltr[x.f]=true;
                    }
                }
            } else {

            }
        }
        F0R(i, m) {
            if(visrtl[i]) continue;
            vt<pair<int,int>> here;
            set<pair<int,int>> added;
            here.push_back({i, 1});
            bool bad = false;
            while(true) {
                auto bk = here.back();
                if(added.count(bk)) {
                    bad=true;
                    break;
                }
                added.insert(bk);
                if(bk.s==0) {
                    if(visltr[bk.f]) {
                        if(stuckltr[bk.f]) {
                            bad=true;
                            break;
                        } else {
                            break;
                        }
                    }
                    visltr[bk.f]=true;
                    if(ltrNext[bk.f]==-1) {
                        break;
                    } else {
                        here.push_back({ltrNext[bk.f], 1});
                    }
                } else {
                    if(visrtl[bk.f]) {
                        if(stuckrtl[bk.f]) {
                            bad=true;
                            break;
                        } else {
                            break;
                        }
                    }
                    visrtl[bk.f]=true;
                    if(rtlNext[bk.f]==-1) {
                        break;
                    } else {
                        here.push_back({rtlNext[bk.f], 0});
                    }
                }
            }
            // cout << i << here << bad << endl;
            if(bad) {
                trav(x, here) {
                    if(x.s==1) {
                        stuckrtl[x.f]=true;
                    } else {
                        stuckltr[x.f]=true;
                    }
                }
            } else {

            }
        }
        // cout << stuckrtl << stuckltr << endl;
        int q;
        cin >> q;
        map<int,set<int>> mp3;
        F0R(i, m) {
            int diff = v[i].s-v[i].f;
            diff%=k;
            diff+=k;
            diff%=k;
            mp3[diff].insert(v[i].f);
        }
        map<int,int> inv;
        F0R(i, m) inv[v[i].f]=i;
        trav(x, mp3) x.s.insert(inf);
        while(q--) {
            int x;
            cin >> x;
            int diff = -x%k;
            diff+=k;
            diff%=k;
            if(mp3.count(diff)) {
                auto lb = (*mp3[diff].lower_bound(x));
                // cout << "LINE 333 " << lb << endl;
                if(lb==inf) {
                    cout << "YES" << endl;
                } else if(stuckrtl[inv[lb]]) {
                    cout << "NO" << endl;
                } else {
                    cout << "YES" << endl;
                }
            } else {
                cout << "YES" << endl;
            }
        }
    }
    return 0;
}