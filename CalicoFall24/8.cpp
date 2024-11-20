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
#define vt vector
#define double long double
#define endl "\n"
ll mod = 1000000007;
int inf = 1e9;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct RMQ {
    vt<vt<short>> sparse;
    vt<int> lg;
    RMQ(vt<short> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<short>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=max(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    short getMin(int lo, int hi) {
        int log = lg[hi-lo+1];
        return max(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,m,k;
        cin >> n >> m >> k;
        vt<vt<short>> v(n, vt<short>(m));
        pair<int,int> start, end;
        F0R(i, n) {
            string s = "";
            cin >> s;
            F0R(j, m) {
                if(s[j]=='#') v[i][j]=2;
                else if(s[j]=='*') v[i][j]=1;
                else v[i][j]=0;
                if(s[j]=='S') start = {i,j};
                if(s[j]=='E') end = {i,j};
            }
        }
        vt<RMQ> rows, cols;
        F0R(i, n) {
            rows.add(RMQ(v[i], 23));
        }
        F0R(i, m) {
            vt<short> a;
            F0R(j, n) a.add(v[j][i]);
            cols.add(RMQ(a, 23));
        }
        vt<vt<bool>> dist(n, vt<bool>(m, false)), dist2(n, vt<bool>(m, false));
        dist[start.f][start.s]=dist2[start.f][start.s]=true;
        deque<array<int,4>> pq;
        pq.push_back({0,1,start.f,start.s});
        vt<pair<int,int>> dirs = {{-1,0},{1,0},{0,1},{0,-1}};
        int ans = 1e9;
        while(pq.size()) {
            auto f = pq.front();
            pq.pop_front();
            assert(dist[f[2]][f[3]]);
            if(f[2]==end.f&&f[3]==end.s) {
                ans=f[0];
                break;
            }
            // cout << f << endl;
            // F0R(i, n) {
            //     F0R(j, m) {
            //         if(dist[i][j]||dist2[i][j]) cout << i << " " << j << " " << dist[i][j] << " " << dist2[i][j] << endl;
            //     }
            // }
        //     cout << "lINE 207 " << f << dist[f[2]][f[3]] << " " << dist2[f[2]][f[3]] << endl;
        //             F0R(i, n) {
        //     F0R(j, m) {
        //         if(dist[i][j]!=inf) cout << i << " " << j << " " << dist[i][j] << " " << dist2[i][j] << endl; 
        //     }
        // }
            trav(x, dirs) {
                pair<int,int> nw = {f[2]+x.f, f[3]+x.s};
                if(nw.f<0||nw.s<0||nw.f>=n||nw.s>=m) continue;
                if(v[nw.f][nw.s]==2) continue;

                int clr = f[1];
                if(v[nw.f][nw.s]==1) clr=1;
                if(clr==1) {
                    if(!dist2[nw.f][nw.s]) {
                        dist2[nw.f][nw.s]=true;//f[0]+1;
                        dist[nw.f][nw.s]=true;//min(f[0]+1, dist[nw.f][nw.s]);
                        pq.push_back({f[0]+1, clr, nw.f, nw.s});
                    }

                } else {
                    if(!dist[nw.f][nw.s]) {
                        dist[nw.f][nw.s]=true;//f[0]+1;
                        pq.push_back({f[0]+1, clr, nw.f, nw.s});
                    }

                }
            }   
            //dash right
            if(f[1]==0) continue;
            int lo = f[3], hi = min(f[3]+k+1, m);
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(rows[f[2]].getMin(f[3], mid)==2) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            int clr = 0;
            if(rows[f[2]].getMin(min(m-1,f[3]+1), lo)==1) clr=1;
            if(clr==1) {
                if(!dist2[f[2]][lo]) {
                    dist2[f[2]][lo]=true;//f[0]+1;
                    dist[f[2]][lo]=true;//min(dist[f[2]][0], f[0]+1);
                    pq.push_back({f[0]+1, clr, f[2], lo});
                }

            } else {
                if(!dist[f[2]][lo]) {
                    dist[f[2]][lo]=true;//f[0]+1;
                    pq.push_back({f[0]+1, clr, f[2], lo});
                }

            }
            lo=max(f[3]-k-1, -1);
            hi=f[3];
            while(lo+1<hi) {
                int mid = (lo+hi+1)/2;
                if(rows[f[2]].getMin(mid, f[3])==2) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            clr = 0;
            if(rows[f[2]].getMin(hi,max(0,f[3]-1))==1) clr=1;
            if(clr==1) {
                if(!dist2[f[2]][hi]) {
                    dist2[f[2]][hi]=true;//f[0]+1;
                    dist[f[2]][hi]=true;//min(dist[f[2]][hi], f[0]+1);
                    pq.push_back({f[0]+1, clr, f[2], hi});
                }

            } else {
                if(!dist[f[2]][hi]) {
                    dist[f[2]][hi]=true;//f[0]+1;
                    pq.push_back({f[0]+1, clr, f[2], hi});
                }

            }
            lo = f[2];
            hi = min(f[2]+k+1, n);
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(cols[f[3]].getMin(f[2], mid)==2) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            clr = 0;
            if(cols[f[3]].getMin(min(n-1,f[2]+1), lo)==1) clr=1;
            if(clr==1) {
                if(!dist2[lo][f[3]]) {
                    dist2[lo][f[3]]=true;//f[0]+1;
                    dist[lo][f[3]]=true;//min(dist[lo][f[3]], f[0]+1);
                    pq.push_back({f[0]+1, 1, lo, f[3]});
                }

            } else {
                if(!dist[lo][f[3]]) {
                    // dist2[lo][f[3]]=f[0]+1;
                    dist[lo][f[3]]=true;//f[0]+1;
                    pq.push_back({f[0]+1, 0, lo, f[3]});
                }

            }

            lo=max(f[2]-k-1, -1);
            hi=f[2];
            while(lo+1<hi) {
                int mid = (lo+hi+1)/2;
                if(cols[f[3]].getMin(mid, f[2])==2) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            clr = 0;
            if(cols[f[3]].getMin(hi,max(0,f[2]-1))==1) clr=1;
            if(clr==1) {
                if(!dist2[hi][f[3]]) {
                    dist2[hi][f[3]]=true;//f[0]+1;
                    dist[hi][f[3]]=true;//min(dist[hi][f[3]], f[0]+1);
                    pq.push_back({f[0]+1, 1, hi, f[3]});
                }

            } else {
                if(!dist[hi][f[3]]) {
                    // dist2[lo][f[3]]=f[0]+1;
                    dist[hi][f[3]]=true;//f[0]+1;
                    pq.push_back({f[0]+1, 0, hi, f[3]});
                }

            }
        }
        if(ans==inf) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}