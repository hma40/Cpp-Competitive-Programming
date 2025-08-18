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
vt<int> solve(vt<int> &b, vt<vt<int>> &inv) {
    int n = b.size();
    stack<array<int,4>> s;
    if(n==1) {
        return {1};
    }
    vt<int> a(n);
    // cout << inv << endl;
    if(inv[2].size()>1) {
        a[0]=1;
        s.push({0,n-1,2,n});
    } else {
        a[0]=n;
        s.push({0,n-1,1,n-1});
    }
    while(s.size()) {
        auto tp = s.top();
        // cout << tp << endl;
        s.pop();
        if(tp[0]==tp[1]) continue;
        vt<int> nxt;
        int num = b[tp[0]]+1;
        while(inv[num].size() && inv[num].back()>tp[0]) {
            nxt.add(inv[num].back());
            inv[num].pop_back();
        }
        if(nxt.size()==1) {
            if(inv[num+1].size()>1 && inv[num+1][inv[num+1].size()-2]>tp[0]) {
                a[nxt[0]]=tp[2]++;
            } else {
                a[nxt[0]]=tp[3]--;
            }
            s.push({tp[0]+1, tp[1], tp[2], tp[3]});
        } else {
            tp[3]-=nxt.size();
            int nx = tp[3]+1;
            reverse(begin(nxt),end(nxt));
            // int prev = tp[0]+1;
            F0R(i, nxt.size()) {
                a[nxt[i]]= nx++;
                int nextInd;
                if(i!=nxt.size()-1) nextInd = nxt[i+1]-1;
                else nextInd = tp[1];

                int sz = nextInd-nxt[i]-1;
                // cout << nxt[i] << " " << nextInd << " " << sz << endl;
                s.push({nxt[i], nextInd, tp[2], tp[2]+sz});
                tp[2]+=sz+1;
            }
        }
    }
    return a;
}
struct RMQ {
    vector<vector<int>> sparse, sparse2;
    vector<int> lg;
    RMQ(vector<int> v, int log) {
        lg.resize(v.size()+5);
        for(int i = 2; i < lg.size(); i++) {
        // FOR(i, 2, lg.size()) {
            lg[i]=lg[i/2]+1;
        }
        sparse.resize(v.size(), vector<int>(log, -1));
        sparse2.resize(v.size(), vector<int>(log, -1));
        for(int i = 0; i < v.size(); i++) {
            sparse[i][0]=v[i];
            sparse2[i][0]=v[i];
        }
        for(int i = 1; i < log; i++) {
            
            for(int j = 0; j < (int)v.size()-(1LL<<i)+1; j++) {
                // cout << (int)v.size()-(1LL<<i)+1 << endl;
                // cout << i << " " << j << endl;
                sparse[j][i]=min(sparse[j][i-1], sparse[j+(1<<(i-1))][i-1]);
                sparse2[j][i]=max(sparse2[j][i-1], sparse2[j+(1<<(i-1))][i-1]);
            }
        }
    }
    int getMin(int lo, int hi) {
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
    }
    int getMax(int lo, int hi) {
        int log = lg[hi-lo+1];
        return max(sparse2[lo][log], sparse2[hi-(1<<log)+1][log]);
    }
};
vector<int> check(vector<int> &perm) {
    int n = perm.size();
    vector<int> v;
    vector<int> rightSmaller(n, n);
    vector<int> leftGreater(n, -1);
    for(int i = 0; i < n; i++) {
        while(v.size() && perm[v.back()]>perm[i]) {
            rightSmaller[v.back()]=i;
            v.pop_back();
        }
        v.push_back(i);
    }
    while(v.size()) v.pop_back();
    for(int i = n-1; i >= 0; i--) {
        while(v.size() && perm[v.back()]<perm[i]) {
            leftGreater[v.back()]=i;
            v.pop_back();
        }
        v.push_back(i);
    }
    // cout << leftGreater << endl;
    RMQ r(rightSmaller, 20);
    // vt<int> increasingTil(n);
    // increasingTil[0]=0;
    vector<int> ret(n);
    ret[0]=1;
    for(int i = 1; i < n; i++) {
        if(perm[i]<perm[i-1]) ret[i]=ret[i-1]+1;
        else {
            //between leftGreater[i] and leftGreater[i]
            //want to find first index with rightSmaller[i]>i
            int lo=leftGreater[i], hi=i-1;
            while(lo+1<hi) {
                int mid = (lo+hi+1)/2;
                if(r.getMax(leftGreater[i]+1, mid)>i) {
                    hi=mid;
                } else {
                    lo=mid;
                }
            }
            ret[i]=ret[hi]+1;
        }
    }
    return ret;
}
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
        vt<int> x(n);
        F0R(i, n) cin >> x[i];
        vt<vt<int>> inv(n+2);
        F0R(i, n) inv[x[i]].add(i);
        if(inv[1].size()>1) {
            cout << "NO" << endl;
            continue;
        }
        bool ok = true;
        stack<array<int,3>> s;
        s.push({0,n-1,1});
        while(s.size()) {
            auto tp = s.top();
            s.pop();
            if(tp[0]==tp[1]) continue;
            if(x[tp[0]+1]!=x[tp[0]]+1) {
                ok=false;
                break;
            }
            vt<int> nxt;
            int num = x[tp[0]]+1;
            while(inv[num].size() && inv[num].back()>tp[0]) {
                nxt.add(inv[num].back());
                inv[num].pop_back();
            }
            reverse(begin(nxt),end(nxt));
            if(tp[2]==0 && nxt.size()!=1) {
                ok=false;
                break;
            }
            if(nxt.size()==1) {
                s.push({tp[0]+1, tp[1], 1});
            } else {
                F0R(i, nxt.size()) {
                    int nextInd;
                    if(i!=nxt.size()-1) nextInd = nxt[i+1]-1;
                    else nextInd = tp[1];
                    s.push({nxt[i], nextInd, 0});
                }
            }
        }
        inv = vt<vt<int>>(n+3);
        F0R(i, n) inv[x[i]].add(i);
        if(!ok) {
            cout << "NO" << endl;
            // assert(false);
        } else {
            auto a = solve(x,inv);
            // cout << a << check(a) << endl;
            assert(check(a)==x);            cout << "YES\n";
            F0R(i, n) cout << a[i] << " ";

            cout << endl;
        }
    }
    return 0;
}