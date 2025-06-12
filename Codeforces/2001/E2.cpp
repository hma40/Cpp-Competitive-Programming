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
ll mod = 998244353;
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
        int n,k;
        cin >> n >> k >> mod;
        vt<vt<vt<int>>> one(n, vt<vt<int>>(k+1, vt<int>(k+1)));
        vt<vt<int>> dontcare(n, vt<int>(k+1)), sumdontcare(n, vt<int>(k+1));
        vt<vt<int>> sumone(n, vt<int>(k+1));
        F0R(i, k+1) one[0][i][i]=dontcare[0][i]=sumone[0][i]=sumdontcare[0][i]=1;
        F0R(level, n-1) {
            //to ways: the one with more > the one with less
            FOR(more, 1, k+1) {
                F0R(less, more) {
                    if(more+less>k) continue;
                    one[level+1][more+less][more]+=2*sumone[level][more]*dontcare[level][less];
                    //we are adding more+less+x for any nonnegative x
                    one[level+1][more+less][more]%=mod;
                }
            }
            //to ways 2
            F0R(fir, k+1) {
                F0R(sec, k+1) {
                    if(fir+sec>k) continue;
                    dontcare[level+1][fir+sec]+=dontcare[level][fir]*dontcare[level][sec];
                    dontcare[level+1][fir+sec]%=mod;
                }
            }
            F0R(more, k+1) {
                FOR(i, 1, k+1) {
                    one[level+1][i][more]+=one[level+1][i-1][more];
                    one[level+1][i][more]%=mod;
                }
            }
            FOR(i, 0, k+1) {
                F0R(more, k+1) {
                    sumone[level+1][i]+=one[level+1][i][more];
                    sumone[level+1][i]%=mod;
                }
            }
            FOR(i, 1, k+1) {
                dontcare[level+1][i]+=dontcare[level+1][i-1];
                dontcare[level+1][i]%=mod;
            }
            sumdontcare[level+1][0]=dontcare[level+1][0];
            FOR(i, 1, k+1) {
                sumdontcare[level+1][i]=sumdontcare[level+1][i]+dontcare[level+1][i];
                sumdontcare[level+1][i]%=mod;
            }
            FOR(sum, 0, k+1) {
                FOR(bigger, 1, k+1) {
                    one[level+1][sum][bigger]+=one[level+1][sum][bigger-1];
                    one[level+1][sum][bigger]%=mod;
                }
            }
        }
        // cout << sumone.back().back() << endl;
        vt<vt<vt<int>>> notroot(n, vt<vt<int>>(k+1, vt<int>(k+1))), root(n, vt<vt<int>>(k+1, vt<int>(k+1))), sumnotroot(n, vt<vt<int>>(k+1, vt<int>(k+1))), sumroot(n, vt<vt<int>>(k+1, vt<int>(k+1)));
        // continue;
        /*
        notroot[i][j][k]
        - above root
        - level i
        - sum=j
        - first child = k
        (note: there must be two layers below it since LCA cannot be the bottom of the tree)
        root[i][j][k]
        - same states as above
        just need 1>2>3 to be fine
        */
        FOR(sum, 1, k+1) {
            FOR(bigger, 1, k+1) {
                int smaller = max(-1LL, min(bigger-1, sum-bigger));
                root[1][sum][bigger]=2*(smaller+1);
            }
            sumroot[1][sum][k]=root[1][sum][k];
            R0F(i, k) {
                sumroot[1][sum][i]=sumroot[1][sum][i+1]+root[1][sum][i];
                sumroot[1][sum][i]%=mod;
            }
        }
        // continue;
        FOR(depth, 2, n) {
            FOR(biggerchild, 0, k+1) {
                FOR(smallerchild, 1, k+1) {
                    if(biggerchild<=smallerchild) continue;
                    if(biggerchild+smallerchild>k) continue;
                    //note: one[i][j][k] = level i, sum=j, more=k
                    root[depth][biggerchild+smallerchild][biggerchild]+=2*sumone[depth-1][smallerchild]%mod*one[depth-1][biggerchild][smallerchild-1];
                    root[depth][biggerchild+smallerchild][biggerchild]%=mod;
                }
            }
            // assert(false);
            FOR(biggerchild, 0, k+1) {
                FOR(sum, 1, k+1) {
                    root[depth][sum][biggerchild]+=root[depth][sum-1][biggerchild];
                    root[depth][sum][biggerchild]%=mod;
                }
            }
            FOR(sum, 0, k+1) sumroot[depth][sum][k]=root[depth][sum][k];
            F0R(sum, k+1) {
                R0F(i, k) {
                    sumroot[depth][sum][i]=sumroot[depth][sum][i+1]+root[depth][sum][i];
                    sumroot[depth][sum][i]%=mod;
                }
            }
            // assert(false);
            FOR(biggerchild, 0, k+1) {
                FOR(smallerchild, 0, k) {
                    //one child: notroot or root
                    //other child: dont care
                    if(smallerchild>=biggerchild) continue;
                    if(smallerchild+biggerchild>k) continue;
                    notroot[depth][biggerchild+smallerchild][biggerchild]+=2*(sumroot[depth-1][biggerchild][smallerchild+1]+sumnotroot[depth-1][biggerchild][smallerchild+1])%mod*dontcare[depth-1][smallerchild];
                    notroot[depth][biggerchild+smallerchild][biggerchild]%=mod;
                }
            }
            FOR(biggerchild, 0, k+1) {
                FOR(sum, 1, k+1) {
                    notroot[depth][sum][biggerchild]+=notroot[depth][sum-1][biggerchild];
                    notroot[depth][sum][biggerchild]%=mod;
                }
            }
            // assert(false);
            FOR(sum, 0, k+1) sumnotroot[depth][sum][k]=notroot[depth][sum][k];
            F0R(sum, k+1) {
                R0F(i, k) {
                    sumnotroot[depth][sum][i]=sumnotroot[depth][sum][i+1]+notroot[depth][sum][i];
                    sumnotroot[depth][sum][i]%=mod;
                }
            }
        }
        int ans = 0;
        F0R(biggerchild, k+1) {
            ans+=notroot.back().back()[biggerchild];
            ans%=mod;
            ans+=root.back().back()[biggerchild];
            ans%=mod;
        }
        cout << ans << endl;
    }
    return 0;
}