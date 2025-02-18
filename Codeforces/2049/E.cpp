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
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int ql = 33;
int query(int x, int y) {
    assert(ql>0);
    ql--;
    cout << "? " << x << " " << y << endl;
    int ans;
    cin >> ans;
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
        ql=33;
        cin >> n;
        int a = query(1,n/2);
        int whichFourth = -1;
        if(a) {
            int b = query(1,n/4);
            int c = query(n/4+1,n/2);
            int d = query(n/2+1,3*n/4);
            if(b&&c) {
                //k<n/4, lying on layer n/2 and layer n/4. We know its not in first half, so lets find it!
                int ans = 0;
                for(int i = n/8; i > 0; i/=2) {
                    if(query(1,ans+i)) {
                        //still lying, range smaller
                    } else {
                        ans+=i;
                    }
                }
                cout << "! " << ans+1 << endl;
            } else {
                //n/2>k>n/4
                if(!b&&!c) {
                    //n/2>=k>n/4, lying on layer n/2 but not layer n/4, lets find it!
                    int ans = n/4;
                    if(d) {
                        whichFourth=3;
                        for(int i = n/8; i > 0; i/=2) {
                            int left = 3*n/4-ans+1;
                            left-=i;
                            if(query(left,3*n/4)) {
                                //not lying, k bigger
                                ans+=i;
                            } else {
                                //lying, k smaller
                            }
                        }
                    } else {
                        whichFourth=4;
                        for(int i = n/8; i > 0; i/=2) {
                            int left = n-ans+1;
                            left-=i;
                            if(query(left,n)) {
                                //not lying, k bigger
                                ans+=i;
                            } else {
                                //lying, k smaller
                            }
                        }
                    }
                    cout << "! " << ans+1 << endl;
                } else {
                    //k>n/2, not lying on either layer
                    //lets find this damn number!
                    int ans = n/2;
                    for(int i = n/4; i > 0; i/=2) {
                        int right = ans+i;
                        if(query(1,right)) {
                            //still not lying
                            ans+=i;
                        } else {
                            
                        }
                    }
                    cout << "! " << ans+1 << endl;
                }
            }
        } else {
            int d = query(1,n/4);
            int c = query(n/2+1,3*n/4);
            int b = query(3*n/4+1,n);
            if(b&&c) {
                //k<n/4, lying on layer n/2 and layer n/4. We know its not in second half, so lets find it!
                int ans = 0;
                for(int i = n/8; i > 0; i/=2) {
                    int left = n;
                    //want range ans+i-1
                    left-=ans+i-1;
                    if(query(left,n)) {
                        //still lying, range smaller
                    } else {
                        ans+=i;
                    }
                }
                cout << "! " << ans+1 << endl;
            } else {
                //k>n/4
                if(!b&&!c) {
                    //n/2>=k>n/4, lying on layer n/2 but not layer n/4, lets find it!
                    int ans = n/4;
                    if(d) {
                        whichFourth=1;
                        for(int i = n/8; i > 0; i/=2) {
                            //ans+i-1? more like [1, ans+i]
                            if(query(1, ans+i)) {
                                //not lying, k bigger
                                ans+=i;
                            } else {
                                //lying, k smaller
                            }
                        }
                    } else {
                        whichFourth=2;
                        for(int i = n/8; i > 0; i/=2) {
                            int left = n/2-ans+1;
                            left-=i;
                            if(query(left,n/2)) {
                                //not lying, k bigger
                                ans+=i;
                            } else {
                                //lying, k smaller
                            }
                        }
                    }
                    cout << "! " << ans+1 << endl;
                } else {
                    //k>n/2, not lying on either layer
                    //lets find this damn number!
                    int ans = n/2;
                    for(int i = n/4; i > 0; i/=2) {
                        int left = n-ans-i+1;//[1,ans+i]? more like [n-ans-i+1,n]
                        if(query(left,n)) {
                            //still not lying
                            ans+=i;
                        } else {
                            
                        }
                    }
                    cout << "! " << ans+1 << endl;
                }
            }
        }
    }
    return 0;
}