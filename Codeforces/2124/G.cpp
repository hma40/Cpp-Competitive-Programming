#include <bits/stdc++.h>
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
struct RMQ {
    vt<vt<int>> sparse;
    vt<int> lg;
    RMQ(vt<int> v, int log) {
        lg.resize(v.size()+5);
        FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vt<int>(log, -1));
        F0R(i, v.size()) {
            sparse[i][0]=v[i];
        }
        FOR(i, 1, log) {
            F0R(j, (int)v.size()-(1LL<<i)+1) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=min(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        if(lo>hi) return inf;
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<pair<int,int>> queries;
        vt<int> prefMin(n);
        prefMin[0]=a[0];
        FOR(i, 1, n) prefMin[i]=min(prefMin[i-1], a[i]);
        vt<int> sum(n);
        sum[0]=a[0];
        FOR(i, 1, n) sum[i]=sum[i-1]+prefMin[i];
        vt<int> suff(n);
        RMQ rmq(a, 20);
        suff[n-1]=a[n-1];
        ROF(i, 0, n-1) {
            int l = i, r = n;
            while(l+1<r) {
                int mid = (l+r)/2;
                if(rmq.getMin(i, mid)<a[i]) {
                    r=mid;
                } else {
                    l=mid;
                }
            }
            if(r==n) {
                suff[i]=a[i]*(n-i);
            } else {
                suff[i]=a[i]*(r-i)+suff[r];
            }
        }
        vt<int> suffInds;
        ROF(i, 1, n) {
            if(prefMin[i]<prefMin[i-1]) {
                trav(x, suffInds) {
                    // cout << i << " " << x << suffInds << endl;
                    if(prefMin[i]+a[x]<=prefMin[i-1]) {
                        queries.add({i, x});
                    } else {
                        queries.add({i,x});
                        break;
                    }
                }
            }
            if(suffInds.size()==0 || a[i]>a[suffInds.back()]) {
                suffInds.add(i);
            }
        }
        trav(x, suffInds) queries.add({0, x});
        // int ans = sum.back();
        suff.add(0);
        vector<int> bruh(n);
        trav(x, queries) {
            int here = 0;
            if(x.f!=0) here+=sum[x.f-1];
            int nwVal = a[x.f]+a[x.s];
            if(x.f!=0) nwVal=min(nwVal, prefMin[x.f-1]);
            int l = x.f, r = n;
            while(l+1<r) {
                int mid = (l+r)/2;
                if(rmq.getMin(x.f+1, mid)<nwVal) {
                    r=mid;
                } else {
                    l=mid;
                }
            }
            here+=nwVal*(r-x.f);

            if(r!=n) {
                here+=suff[r];
            }
            // cout << "LINE 248 " << r << " " << here << endl;
            int M = min({rmq.getMin(0,x.f-1), rmq.getMin(x.f+1, x.s-1), nwVal});
            l=x.s-1;
            r=n;
            while(l+1<r) {
                int mid = (l+r)/2;
                if(rmq.getMin(x.s, mid)<M) {
                    r=mid;
                } else {
                    l=mid;
                }
            }
            // cout << "LINE 264 " << M << " " << r << endl;
            here-=M*(r-x.s);
            // cout << x << here << endl;
            if(r!=n) here-=suff[r];
            bruh[x.s-x.f]=max(bruh[x.s-x.f], here);
        }
        for(int i = n-2; i >= 0; i--) {
            bruh[i]=max(bruh[i], bruh[i+1]);
        }
        // cout << ans << endl;
        F0R(i, n) cout << bruh[i] << " ";
        cout << endl;
        // set<int> uniqs;
        // F0R(i, n) uniqs.insert(bruh[i]);
        // assert(uniqs.size()<7);
        // cerr << a << uniqs.size() << endl;
    }
    return 0;
}
/*


7 4 7 0 8 7 5 0 2 1 
*/