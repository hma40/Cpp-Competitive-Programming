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
// #define endl "\n"
#define enld "\n"
#define double long double
// const ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
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
__int128_t mod = (1LL<<61)-1;
vt<__int128_t> pw;
int sd = 0;
struct Hash {
    vt<__int128_t> hsh;
    Hash(vt<int> s) {
        hsh.resize(s.size()+1);
        F0R(i, s.size()) {
            hsh[i+1]=hsh[i]*sd;
            hsh[i+1]+=s[i];
            hsh[i+1]%=mod;
        }
    }
    int getHash(int left, int right) {
        __int128_t raw = hsh[right+1]-hsh[left]*pw[right-left+1];
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
};
int xx;
void initialize() {
    sd = rnd()%mod;
    xx = 1000005;
    pw.add(1);
    F0R(i, 1000050) {
        pw.add(pw.back()*sd%mod);
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    initialize();
    while(t--) {
        int n,m;
        cin >> n >> m;
        vt<int> a(n), b(n);
        F0R(i, n) cin >> a[i];
        F0R(i, n) cin >> b[i];
        vt<int> nxta(n, -1), nxtb(n, -1), graph(n);
        multiset<int> ms;
        F0R(i, n) ms.insert(a[i]);
        F0R(i, n) {
            if(ms.find(b[i])==ms.end()) break;
            ms.erase(ms.find(b[i]));
        }
        if(ms.size()) {
            cout << "NO" << endl;
            continue;
        }
        vt<vt<int>> inva(m+1), invb(m+1);
        F0R(i, n) {
            inva[a[i]].add(i);
            invb[b[i]].add(i);
        }
        F0R(i, n) {
            if(a[i]==m) continue;
            auto bruh = lower_bound(begin(inva[a[i]+1]), end(inva[a[i]+1]), i)-begin(inva[a[i]+1]);
            if(bruh==inva[a[i]+1].size()) {
                bruh = 0;
            }
            nxta[i]=inva[a[i]+1][bruh];
        }
        // assert(false);
        F0R(i, n) {
            if(b[i]==m) continue;
            auto bruh = lower_bound(begin(invb[b[i]+1]), end(invb[b[i]+1]), i)-begin(invb[b[i]+1]);
            // cout << i << " " << bruh << endl;
            if(bruh==invb[b[i]+1].size()) {
                bruh = 0;
            }
            // cout << i << " " << bruh << endl;
            nxtb[i]=invb[b[i]+1][bruh];
        }
        // cout << nxta << endl << nxtb << endl;
        // assert(false);
        FOR(i, 1, m+1) {
            FOR(j, 1, inva[i].size()) {
                graph[inva[i][j]]=inva[i][j-1];
            }
            graph[inva[i][0]]=inva[i].back();
        }
        // assert(false);
        SegTree st(n);
        vt<int> c(n), ca(n);
        FOR(i, 1, m+1) {
            F0R(j, invb[i].size()) c[invb[i][j]]=j;
        }
        FOR(i, 1, m+1) {
            F0R(j, invb[i].size()) ca[inva[i][j]]=j;
        }
        vt<vt<int>> lessA(m+1), moreA(m+1), lessB(m+1), moreB(m+1);
        FOR(i, 2, m+1) {
            trav(x, inva[i-2]) st.set(x, 0);
            trav(x, inva[i-1]) st.set(x, 1);
            FOR(j, 1, inva[i].size()) {
                lessA[i].add(st.rangeQuery(inva[i][j-1], inva[i][j]));
            }
            lessA[i].add(st.rangeQuery(inva[i].back(), n-1)+st.rangeQuery(0, inva[i][0]));
        }
        st = SegTree(n);
        FOR(i, 2, m+1) {
            trav(x, invb[i-2]) st.set(x, 0);
            trav(x, invb[i-1]) st.set(x, 1);
            FOR(j, 1, invb[i].size()) {
                lessB[i].add(st.rangeQuery(invb[i][j-1], invb[i][j]));
            }
            lessB[i].add(st.rangeQuery(invb[i].back(), n-1)+st.rangeQuery(0, invb[i][0]));
        }
        st = SegTree(n);
        FOR(i, 1, m) {
            trav(x, inva[i]) st.set(x, 0);
            trav(x, inva[i+1]) st.set(x, 1);
            FOR(j, 1, inva[i].size()) {
                moreA[i].add(st.rangeQuery(inva[i][j-1], inva[i][j]));
            }
            moreA[i].add(st.rangeQuery(inva[i].back(), n-1)+st.rangeQuery(0, inva[i][0]));
        }
        st = SegTree(n);
        FOR(i, 1, m) {
            trav(x, invb[i]) st.set(x, 0);
            trav(x, invb[i+1]) st.set(x, 1);
            FOR(j, 1, invb[i].size()) {
                moreB[i].add(st.rangeQuery(invb[i][j-1], invb[i][j]));
            }
            moreB[i].add(st.rangeQuery(invb[i].back(), n-1)+st.rangeQuery(0, invb[i][0]));
        }
        st = SegTree(n);
        while(lessA[1].size()<moreA[1].size()) {
            lessA[1].add(0);
            lessB[1].add(0);
        }
        while(moreA[m].size()<lessA[m].size()) {
            moreA[m].add(0);
            moreB[m].add(0);
        }
        // assert(false);
        bool ok = true;
        set<int> which;
        F0R(i, inva[1].size()) which.insert(i);
        vt<vt<int>> sparse(n, vt<int>(20));
        F0R(i, n) sparse[i][0]=graph[i];
        FOR(j, 1, 20) {
            F0R(i, n) {
                sparse[i][j]=sparse[sparse[i][j-1]][j-1];
            }
        }
        // assert(false);
        auto jump = [&sparse](int u, int times)->int{
            R0F(i, 20) {
                if(times&(1<<i)) u = sparse[u][i];
            }
            return u;
        };
        FOR(i, 1, m+1) {
            // cout << i << " " << which << endl;
            vt<int> temp, temp2;
            F0R(j, moreA[i].size()) {
                // s.insert({lessA[i][j], moreA[i][j]});
                temp.add((lessA[i][j]*xx+moreA[i][j])%mod);
            }
            F0R(j, moreA[i].size()) {
                // s.insert({lessA[i][j], moreA[i][j]});
                temp.add((lessA[i][j]*xx+moreA[i][j])%mod);
            }
            F0R(j, moreB[i].size()) {
                // s.insert({lessA[i][j], moreA[i][j]});
                temp2.add((lessB[i][j]*xx+moreB[i][j])%mod);
            }
            // cout << i << temp << temp2 << endl;
            bool found = false;
            Hash h1(temp), h2(temp2);
            set<int> nx;
            FOR(j, temp2.size()-1, temp.size()) {
                if(h1.getHash(j-temp2.size()+1, j) == h2.getHash(0, temp2.size()-1)) {
                    
                    if(which.count(j-temp2.size()+1)) {
                        // cout << "GOT HERE LINE 379 " << j-temp2.size()+1 << endl;
                        if(i==m) {
                            found=true;
                            break;
                        }
                        int tmp = nxta[inva[i][j-temp2.size()+1]];
                        int tmp2 = nxtb[invb[i][0]];
                        // cout << tmp << " " << tmp2 << " " << c[tmp2] << endl;
                        int tmp3 = jump(tmp, c[tmp2]);
                        nx.insert(ca[tmp3]);
                        found=true;
                    }
                }
            }
            
            if(!found) ok =false;
            swap(nx, which);
        }
        if(ok) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
/*
1
6 4

2 4 6 7 3 1 5 4 6
6 7 3 5 6 4 2 4 1

*/