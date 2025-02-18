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
#define double long double
ll mod = 1000000007;
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
        int log = lg[hi-lo+1];
        return min(sparse[lo][log], sparse[hi-(1<<log)+1][log]);
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
        int n;
        string s;
        cin >> n >> s;
        vt<int> leftNum(n+1),leftTot(n+1),rightNum(n+1),rightTot(n+1);
        F0R(i, n) {
            if(s[i]=='<') {
                leftNum[i+1]=1;
                leftTot[i+1]=i;
            } else {
                rightNum[i+1]=1;
                rightTot[i+1]=i;
            }
        }
        FOR(i, 1, n+1) {
            leftNum[i]+=leftNum[i-1];
            rightNum[i]+=rightNum[i-1];
            leftTot[i]+=leftTot[i-1];
            rightTot[i]+=rightTot[i-1];
        }
        F0R(i, n) {
            int here = 0;
            int rightOps = leftNum[n]-leftNum[i+1];
            int leftOps = rightNum[i];
            if(s[i]=='<') {
                if(leftOps<=rightOps) {
                    //will exit left stage after bouncing leftOps times on both sides
                    /*
                    <><<<>
                    3 - 2(1) + 2(2) - 2(2) + 2(3)
                    */
                    here+=i+1;
                    here-=2*rightTot[i];
                    int lo = i+1, hi = n+1;
                    while(lo+1<hi) {
                        int mid = (lo+hi)/2;
                        if(leftNum[mid]-leftNum[i+1]<=leftOps) {
                            //if the number of "<" from i+1 to mid-1 is less than or equal to leftOps, set lower bound to mid
                            lo=mid;
                        } else {
                            hi=mid;
                        }
                    }
                    here+=2*(leftTot[lo]-leftTot[i+1]);
                } else {
                    here+=n-i;
                    here+=2*(leftTot[n]-leftTot[i+1]);
                    int lo = -1, hi = i;
                    while(lo+1<hi) {
                        int mid = (lo+hi+1)/2;
                        if(rightNum[i]-rightNum[mid]<=rightOps) {
                            hi=mid;
                        } else {
                            lo=mid;
                        }
                    }
                    here-=2*(rightTot[i]-rightTot[lo]);
                    here+=2*i;
                }
            } else {
                if(rightOps<=leftOps) {
                    //will exit left stage after bouncing leftOps times on both sides
                    /*
                    <><<<>
                    3 - 2(1) + 2(2) - 2(2) + 2(3)
                    */
                    here+=n-i;
                    here+=2*(leftTot[n]-leftTot[i+1]);
                    int lo = -1, hi = i;
                    while(lo+1<hi) {
                        int mid = (lo+hi+1)/2;
                        if(rightNum[i]-rightNum[mid]<=rightOps) {
                            hi=mid;
                        } else {
                            lo=mid;
                        }
                    }
                    // cout << lo << " " << hi << endl;
                    here-=2*(rightTot[i]-rightTot[hi]);
                } else {
                    here+=i+1;
                    here-=2*rightTot[i];
                    int lo = i+1, hi = n+1;
                    while(lo+1<hi) {
                        int mid = (lo+hi)/2;
                        if(leftNum[mid]-leftNum[i+1]<=leftOps) {
                            //if the number of "<" from i+1 to mid-1 is less than or equal to leftOps, set lower bound to mid
                            lo=mid;
                        } else {
                            hi=mid;
                        }
                    }
                    // cout << lo << " " << hi << endl;
                    here+=2*(leftTot[hi]-leftTot[i+1]);
                    here-=2*i;
                }
            }
            
            cout << here << " ";
        }
        cout << endl;
    }
    return 0;
}