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
#define enld "\n"
#define double long double
const ll mod = 998244353;
const ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int bexpo(int b, int e) {
    int ans = 1;
    while(e) {
        if(e&1) ans=ans*b%mod;
        e>>=1;
        b=b*b%mod;
    }
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
        vt<int> prob(n), probAlive(n);
        F0R(i, n) {
            int p,q;
            cin >> p >> q;
            prob[i]=p*bexpo(q,mod-2)%mod;
            probAlive[i]=(mod+1-prob[i])%mod;
        }
        vt<int> allNeighborsDead(n, 1);
        vt<vt<int>> adj(n);
        F0R(i, n-1) {
            int u,v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].add(v);
            adj[v].add(u);
        }
        F0R(i, n) {
            trav(x, adj[i]) {
                allNeighborsDead[i]*=prob[x];
                allNeighborsDead[i]%=mod;
            }
            allNeighborsDead[i]*=probAlive[i];
            allNeighborsDead[i]%=mod;
        }
        // cout << allNeighborsDead << endl;
        vt<int> chanceLeaf(n,0);
        int ans = 0;
        F0R(i, n) {
            trav(x, adj[i]) {
                int orig = allNeighborsDead[i];
                orig*=bexpo(prob[x], mod-2);
                orig%=mod;
                orig*=probAlive[x];
                orig%=mod;
                chanceLeaf[i]+=orig;
                chanceLeaf[i]%=mod;
            }
        }
        // cout << chanceLeaf << endl;
        int tot = 0;
        F0R(i, n) tot+=chanceLeaf[i];
        tot%=mod;
        //calculate contribution for two adjacent vertices
        // cout << "CASE 1: TWO ADJACENT" << endl;
        F0R(i, n) {
            trav(x, adj[i]) {
                int iGood = allNeighborsDead[i];
                iGood*=bexpo(prob[x], mod-2);
                iGood%=mod;
                iGood*=probAlive[x];
                iGood%=mod;
                //iGood contains probability i alive * x alive * all neighbors of i dead
                int xGood = allNeighborsDead[x];
                xGood*=bexpo(probAlive[x], mod-2);
                xGood%=mod;
                xGood*=bexpo(prob[i], mod-2);
                xGood%=mod;
                //xGood contains probability all neighbors of x except i alive
                // iGood*=
                ans+=iGood*xGood;
                ans%=mod;
                // cout << i << " " << x << " " << (iGood*xGood)%mod << endl;
                // cout << i << " " << x << " " << iGood << " " << xGood << " " << (iGood*xGood)%mod << endl;
            }
        }
        //calculate contribution for two vertices one apart - loop through the center
        // vt<int> chances(n);
        // cout << "CASE 2: TWO DISTANCE 2, CENTER ACTIVE" << endl;
        F0R(center, n) {
            //need center to be alive and two adjacent vertices to all be alive
            //a1a2+a1a3+a1a4+... = 0.5(a1(a2+...+an)+a2(a1+...+an)+...)
            int sum = 0;
            vt<int> chances;
            trav(x, adj[center]) {
                chances.add((allNeighborsDead[x]*bexpo(prob[center], mod-2))%mod);
                sum+=chances.back();
            }
            sum%=mod;
            int here = 0;
            F0R(i, chances.size()) {
                here+=chances[i]*(sum+mod-chances[i]);
                here%=mod;
            }
            // cout << sum << enld;
            // here*=bexpo(2, mod-2);
            // here%=mod;
            here*=probAlive[center];
            here%=mod;
            // cout << center << " " << here << endl;
            ans+=here;
        }
        // cout << "CASE 3: TWO DISTANCE 2, CENTER INACTIVE" << endl;
        F0R(center, n) {
            vt<int> hmm;
            trav(x, adj[center]) {
                int temp = chanceLeaf[x];
                temp-=allNeighborsDead[x]*bexpo(prob[center], mod-2)%mod*probAlive[center]%mod;
                temp%=mod;
                temp+=mod;
                temp%=mod;
                hmm.add(temp);
            }
            int sum = 0;
            trav(x, hmm) sum+=x;
            sum%=mod;
            int here = 0;
            // cout << center << " " << hmm << endl;
            F0R(i, hmm.size()) {
                here+=hmm[i]*(sum-hmm[i]);
                here%=mod;
                here+=mod;
                here%=mod;
            }
            here*=bexpo(prob[center], mod-2);
            here%=mod;
            // cout << center << " " << here << endl;
            ans+=here;
        }

        // cout << "CASE 4: DISTANCE AT LEAST THREE" << enld;
        vt<int> atLeastThree(n);
        vt<int> oneAway(n);
        F0R(i, n) {
            trav(x, adj[i]) {
                oneAway[i]+=chanceLeaf[x];
            }
            oneAway[i]%=mod;
        }
        F0R(i, n) {
            atLeastThree[i]=tot;
            atLeastThree[i]-=chanceLeaf[i];
            trav(x, adj[i]) {
                atLeastThree[i]-=chanceLeaf[x];
                atLeastThree[i]-=oneAway[x];
                atLeastThree[i]+=chanceLeaf[i];
            }
            atLeastThree[i]%=mod;
            atLeastThree[i]+=mod;
            atLeastThree[i]%=mod;
        }
        // cout << atLeastThree << endl;
        F0R(i, n) {
            ans+=chanceLeaf[i]*atLeastThree[i];
            ans%=mod;
        }
        ans*=bexpo(2,mod-2);
        ans%=mod;
        cout << ans << endl;
    }
    return 0;
}
/*
1
4
1 3
1 3
1 3
1 3
1 2
2 3
3 4
*/