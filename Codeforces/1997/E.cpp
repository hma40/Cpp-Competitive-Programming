#include <bits/stdc++.h>
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
// #define int long long
#define vt vector
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<vt<int>> atLeast;
vt<int> levels;
vt<int> bf;   
int n,q;
int cur = -1;
void bruteForce(int i) {
    bf.assign(n, 0);
    int needed = i;
    cur=i;
    int lvl = 1;
    F0R(x, n) {
        bf[x]=lvl;
        if(levels[x]>=lvl) {
            needed--;
            if(needed==0) {
                needed=i;
                lvl++;
            }
        }
    }
    // cout << bf << endl;
}
int cur2 = -1;
vt<int> smart;
void bsearch(int i) {
    cur2=i;
    smart.assign(455, n);
    int curq = 0;
    int lvl = 1;
    while(curq<n) {
        if(atLeast[lvl][n]-atLeast[lvl][curq]<i) {
            //cannot level up anymore
            smart[lvl]=n-1;
            curq=n;
            break;
        }
        int fir = min(n, curq+i-1), las = n;
        while(fir+1<las) {
            int mid = (fir+las)/2;
            if(atLeast[lvl][mid]-atLeast[lvl][curq]<=i) {
                //in second half
                fir=mid;
            } else {
                las=mid;
            }
        }
        // cout << i << " "/ << lvl << " " << cur << " " << fir << " " << las << " " << atLeast[lvl][cur] << " " << atLeast[lvl][fir] << " " << atLeast[lvl][las] << endl; 
        if(atLeast[lvl][las]-atLeast[lvl][curq]<=i) {
            smart[lvl]=las-1;
            curq=las;
        } else {
            smart[lvl]=fir-1;
            curq=fir;
        }
        lvl++;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    cin >> n >> q;
    atLeast.assign(455, vt<int>(n+1));
    levels.resize(n);
    F0R(i, n) cin >> levels[i];
    F0R(i, n) {
        // cout << "LINE 168 " << i << endl;
        F0R(j, 455) {
            atLeast[j][i+1]=atLeast[j][i];
        }
        R0F(j, 1+min(454, levels[i])) {
            atLeast[j][i+1]++;
        }
    }
    vt<vt<int>> v(q, vt<int>(3));
    F0R(i, q) {
        // cout << "LINE 178 " << i << endl;
        // int a,b;
        cin >> v[i][1] >> v[i][0]; 
        v[i][1]--;
        v[i][2]=i;
    }
    sort(begin(v),end(v));
    // assert(false);
    vt<bool> ans(q);
    F0R(i, q) {
        if(v[i][0]<455) {
            if(cur!=v[i][0]) {
                bruteForce(v[i][0]);   
            }
            if(bf[v[i][1]]<=levels[v[i][1]]) {
                ans[v[i][2]]=true;
            }
        } else {
            if(cur2!=v[i][0]) {
                bsearch(v[i][0]);

            }
            if(levels[v[i][1]]>=455) {
                ans[v[i][2]]=true;
            } else {
                if(smart[levels[v[i][1]]]>=v[i][1]) {
                    ans[v[i][2]]=true;
                }
            }
        }
    }
    // cout << ans << endl;
    F0R(i, q) {
        if(ans[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    //atleast[i] = how many monsters from 0 to i-1 with level at least i
    // vt<vt<int>> bruteForce(455, vt<int>(n));
    //bruteforce[i][j]: k=i, level=j (before fighting this monster)
    // cout << bruteForce[2] << endl;

    // cout << atLeast[1] << atLeast[2] << endl;
    // vt<vt<int>> firstLevel(200001, vt<int>(455, n));
    //firstLevel[i][j]=x: k=i, j=level, x=last index with level j
    // cout << atLeast[2] << endl;
    // cout << firstLevel[3] << endl;

    // cout << firstLevel[2] << endl;
    return 0;
}
/*

for runs with small k: brute force

for runs with large k: final level cannot be >n/k, so bsearch for next level up

*/