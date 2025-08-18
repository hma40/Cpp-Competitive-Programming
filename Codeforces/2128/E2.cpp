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
struct SegTree {
    int n;
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    int walk(int pos) {
        int ind = 1;
        while(ind<n) {
            if(tree[2*ind]>=pos) {
                ind*=2;
            } else {
                pos-=tree[2*ind];
                ind*=2;
                ind++;
            }
        }
        return ind-n;
    }
    int rangeQuery(int a, int b) {
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            a/=2;
            b/=2;
        }
        return ans;
    }
};
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
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        if(n==k) {
            sort(begin(a),end(a));
            if(a.size()%2) {
                cout << 1 << endl;
                cout << a[n/2] << " " << 1 << " " << n << endl;
            } else {
                cout << a[n/2]-a[n/2-1]+1 << endl;
                FOR(i, a[n/2-1], a[n/2]+1) {
                    cout << i << " " << 1 << " " << n << endl;
                }
            }
            continue;
        }

        vt<int> psum(n+1);
        vt<int> smax(n+1);
        auto getLargest = [&]()->pair<int,int>{
                            int lo = 0, hi = n+1;
            while(lo+1<hi) {

            int mid = (lo+hi)/2;
            F0R(i, n) {
                if(a[i]>=mid) {
                    psum[i+1]=psum[i]+1;
                } else {
                    psum[i+1]=psum[i]-1;
                }
            }
            smax.back()=psum.back();
            R0F(i, n) smax[i]=max(smax[i+1],psum[i]);
            bool ok = false;
            F0R(i, n+1-k) {
                if(smax[i+k]>=psum[i]) {
                    ok=true;
                    break;
                }
            }
            if(ok) {
                lo=mid;
            } else {
                hi=mid;
            }
        }
        F0R(i, n) {
            if(a[i]>=lo) {
                psum[i+1]=psum[i]+1;
            } else {
                psum[i+1]=psum[i]-1;
            }
        }
        smax.back()=psum.back();
        R0F(i, n) smax[i]=max(smax[i+1],psum[i]);
        pair<int,int> ret;
        F0R(i, n+1-k) {
            if(smax[i+k]>=psum[i]) {
                ret.f=i;
                // cout << lo << " " << i+1 << " ";
                FOR(j, i+k, n+1) {
                    if(psum[j]>=psum[i]) {
                        // cout << j;
                        ret.s=j-1;
                        return {ret.f,ret.s};
                        // break;
                    }
                }
                // cout << endl;
                // break;
            } else {
                continue;
            }
        }

        };


                auto getSmallest = [&]()->pair<int,int>{
                int lo = 0, hi = n+1;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            F0R(i, n) {
                if(a[i]>mid) {
                    psum[i+1]=psum[i]+1;
                } else {
                    psum[i+1]=psum[i]-1;
                }
            }
            smax.back()=psum.back();
            R0F(i, n) smax[i]=min(smax[i+1],psum[i]);
            bool ok = false;
            F0R(i, n+1-k) {
                if(smax[i+k]<=psum[i]) {
                    ok=true;
                    break;
                }
            }
            if(ok) {
                hi=mid;
            } else {
                lo=mid;
            }
        }
        F0R(i, n) {
            if(a[i]>hi) {
                psum[i+1]=psum[i]+1;
            } else {
                psum[i+1]=psum[i]-1;
            }
        }
        smax.back()=psum.back();
        R0F(i, n) smax[i]=min(smax[i+1],psum[i]);
        pair<int,int> ret;
        F0R(i, n+1-k) {
            if(smax[i+k]<=psum[i]) {
                ret.f=i;
                // cout << lo << " " << i+1 << " ";
                FOR(j, i+k, n+1) {
                    if(psum[j]<=psum[i]) {
                        // cout << j;
                        ret.s=j-1;
                        return {ret.f,ret.s};
                        // break;
                    }
                }
                // cout << endl;
                // break;
            } else {
                continue;
            }
        }

        };
        auto larg = getLargest(), smol = getSmallest();
        // cout << larg << " " << smol << endl;
        if(smol.s%2==smol.f%2) {
            if(smol.f!=0) smol.f--;
            else smol.s++;
        }
        if(larg.s%2==larg.f%2) {
            if(larg.f!=0) larg.f--;
            else larg.s++;
        }
        set<int> need;
        F0R(i, n+1) need.insert(i);
        SegTree st(n+1);
        int l = smol.f, r = smol.s;
        // assert(false);
        // cout << smol << endl;
        // cerr << larg << smol << endl;
        FOR(i, smol.f, smol.s+1) {
            st.add(a[i],1);
        }
        // assert(false);
        vt<pair<int,int>> ans(n+1);
        auto doStuff = [&]()->void{
            // cout << "LINE 373 " << l << " " << r << endl;
            int sz = r-l+1;
            int lo = st.walk(sz/2), hi = st.walk(sz/2+1);
            // cout << lo << " " << hi << endl;
            while(true) {
                auto lb = need.lower_bound(lo);
                if(lb==need.end()) break;
                if((*lb)>hi) break;
                ans[*lb]={l+1,r+1};
                need.erase(lb);
            }
        };
        while(true) {
            doStuff();
            if(l>=2) {
                st.add(a[l-1],1);
                st.add(a[l-2],1);
                l-=2;
                continue;
            } 
            if(r<n-2) {
                st.add(a[r+1],1);
                st.add(a[r+2],1);
                r+=2;
                continue;
            }
            if(l>=1 && r<n-1) {
                st.add(a[l-1],1);
                st.add(a[r+1],1);
                l--;
                r++;
            }
            break;
        }
        l=larg.f;
        r=larg.s;
        st = SegTree(n+1);
                FOR(i, larg.f, larg.s+1) {
            st.add(a[i],1);
        }
        while(true) {
            doStuff();
            if(l>=2) {
                st.add(a[l-1],1);
                st.add(a[l-2],1);
                l-=2;
                continue;
            } 
            if(r<n-2) {
                st.add(a[r+1],1);
                st.add(a[r+2],1);
                r+=2;
                continue;
            }
            if(l>=1 && r<n-1) {
                st.add(a[l-1],1);
                st.add(a[r+1],1);
                l--;
                r++;
            }
            break;
        }
        cout << n+1-need.size() << endl;
        F0R(i, n+1) {
            if(ans[i].f!=0) {
                cout << i << " " << ans[i].f << " " << ans[i].s << endl;
            }
        }
    }
    return 0;
}
/*
0 -1 -2 -1 -2 -3
*/