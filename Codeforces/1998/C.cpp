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
int getMidTo(vt<pair<int,int>> &v, int leftMid, int median) {
    int unmov=0;
    vt<int> mov;
    F0R(i, v.size()) {
        if(v[i].f>=median) break;
        if(v[i].s==0) {
            unmov++;
        } else {
            mov.add(v[i].f);
        }
    }
    // cout << unmov << mov << leftMid << " " << median << endl;
    int fixes = unmov+mov.size()-leftMid;
    // if(unmov>leftMid) return inf;
    if(fixes<=0) return 0;
    if(fixes>mov.size()) return inf;
    int ans = 0;
    F0R(i, fixes) {
        ans+=median-mov[mov.size()-i-1];
    }
    // cout << "RETURNING " << ans << " FOR " << median << endl;
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
        int n,k;
        cin >> n >> k;
        vt<pair<int,int>> v(n);
        // F0R(i, n) cin >> v[i].f >> v[i].s;
        F0R(i, n) cin >> v[i].f;
        F0R(i, n) cin >> v[i].s;
        sort(begin(v),end(v));
        vt<int> canChange,noChange;
        vt<int> oldInd0,oldInd1;
        F0R(i,n) {
            if(v[i].s==0) {
                noChange.add(v[i].f);
                oldInd0.add(i);
            }
            else {
                oldInd1.add(i);
                canChange.add(v[i].f);
            }
        }
        // sort(begin(noChange),end(noChange));
        // sort(begin(canChange),end(canChange));

        int leftMid = (n-2)/2;
        int rightMid = leftMid+1;
        // cout << n << " " << leftMid << " " << rightMid << endl;
        //use a.back()+a[leftMid]
        if(canChange.size()==0) {
            cout << noChange[leftMid]+noChange.back() << endl;
            continue;
        }
        if(noChange.size()==0) {
            cout << canChange[leftMid]+canChange.back()+k << endl;
            continue;
        }
        //work on maximizing back OR maximizing mid
        // int case0=0,case1=0;
        int ans = 0;
        int maxBruh = canChange.back()+k;
        if(oldInd1.back()==leftMid) {
            if(maxBruh<v[leftMid+1].f) {
                ans=max(ans, maxBruh+v.back().f);
            } else {
                ans=max(ans, maxBruh+v[leftMid+1].f);
                ans=max(ans, v.back().f+v[leftMid+1].f);
            }
        } else if(oldInd1.back()<leftMid) {
            if(maxBruh>=v[leftMid+1].f) {
                ans=max(ans, maxBruh+v[leftMid+1].f);
            }
        }
        ans=max(ans, maxBruh+v[leftMid].f);
        ans=max(ans, v.back().f+v[leftMid].f);
        int lo = 0, hi = 2e9+5;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(getMidTo(v, leftMid, mid)>k) {
                hi=mid;
            } else {
                lo=mid;
            }
        }
        // cout << "LINE 221 " << lo << endl;
        if(lo>v.back().f) {
            assert(ans>=lo+lo);
            ans=max(ans, lo+lo);
        }
        ans=max(ans, lo+v.back().f);
        cout << ans << endl;
    }
    return 0;
}
/*
2 5 11 15 15
1 1 1 0 0
*/