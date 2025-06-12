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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
class FenwickTree {
private:
    int n;
    std::vector<T> bit;  // 1-based Fenwick tree array
    std::vector<T> arr;  // underlying array to track current values

public:
    // Construct a Fenwick Tree of size _n (0-based interface, internally 1-based)
    FenwickTree(int _n)
        : n(_n),
          bit(n + 1, T()),
          arr(n, T())
    {}

    // add(index, x): increase the value at index 'idx' (0-based) by 'v'
    void add(int idx, T v) {
        assert(idx >= 0 && idx < n);
        arr[idx] += v;
        int i = idx + 1;  // switch to 1-based
        while (i <= n) {
            bit[i] += v;
            i += (i & -i);
        }
    }

    // set(index, x): set the value at index 'idx' (0-based) to 'v'
    void set(int idx, T v) {
        assert(idx >= 0 && idx < n);
        T delta = v - arr[idx];
        add(idx, delta);
    }

    // prefix_sum(idx): returns sum of elements from 0 to idx (inclusive)
    T prefix_sum(int idx) const {
        assert(idx >= 0 && idx < n);
        T result = T();
        int i = idx + 1;  // switch to 1-based
        while (i > 0) {
            result += bit[i];
            i -= (i & -i);
        }
        return result;
    }

    // sum(left, right): returns sum of elements from left to right (inclusive)
    T sum(int left, int right) const {
        if(left>right) return 0;
        if (left == 0) {
            return prefix_sum(right);
        } else {
            return prefix_sum(right) - prefix_sum(left - 1);
        }
    }
};
int invs(vt<int> perm) {
    FenwickTree<int> ft(perm.size()+1);
    int ans = 0;
    int n = perm.size();
    trav(x, perm) {
        ans+=ft.sum(x+1, n);
        ft.set(x, 1);
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        set<array<int,4>> iv;
        auto intersects = [](int w, int x, int y, int z)->bool{
            return max(w,y)<=min(x,z);
        };
        bool ok = true;
        F0R(i, m) {
            int l,r;
            cin >> l >> r;
            l--;
            r--;
            vt<array<int,4>> del;
            trav(x, iv) {
                if(intersects(l, r, x[0], x[1])) del.add(x);
            }
            trav(x, del) iv.erase(x);
            int small_ends_l = l, small_ends_r = r-1;
            trav(x, del) {
                small_ends_l = max(small_ends_l, x[2]);
                small_ends_r = min(small_ends_r, x[3]);
                l=min(l, x[0]);
                r=max(r, x[1]);
            }
            if(small_ends_l>small_ends_r) {
                ok=false;
            } else {
                iv.insert({l,r,small_ends_l,small_ends_r});
            }
        }
        if(!ok) {
            cout << -1 << endl;
            continue;
        }
        vt<array<int,4>> ivs(begin(iv),end(iv));
        vt<int> sum_sz;
        sum_sz.add(0);
        F0R(i, ivs.size()) {
            sum_sz.add(sum_sz.back()+ivs[i][1]-ivs[i][3]);
        }
        // cout << ivs << endl;
        int smaller = 0;
        m=ivs.size();
        F0R(i, ivs.size()) smaller+=ivs[i][2]-ivs[i][0]+1;
        int bestInvs = -inf;
        // cout << sum_sz << endl;
        int lo = smaller, hi = n-sum_sz.back()+1;
        auto f = [&](int lesser)->int{
            vt<int> here(n);
            int supper = lesser, lupper = n;
            int ind = 0;
            F0R(i, n) {
                if(ind==m) {
                    if(lupper==lesser)
                    here[i]=supper--;
                    else here[i]=lupper--;
                    continue;
                }
                if(ivs[ind][0]>i) {
                    int big_left = lupper-lesser;
                    int need_big_left = sum_sz.back()-sum_sz[ind]+1;
                    if(big_left>=need_big_left) {
                        here[i]=lupper--;
                    } else {
                        here[i]=supper--;
                    }
                } else if(ivs[ind][1]==i) {
                    here[i]=lupper--;
                    ind++;
                } else if(ivs[ind][2]>=i) {
                    here[i]=supper--;
                } else {
                    int big_left = lupper-lesser;
                    int need_big_left = sum_sz.back()-sum_sz[ind+1]+ivs[ind][1]-i+1;
                    if(big_left>=need_big_left) {
                        here[i]=lupper--;
                    } else {
                        here[i]=supper--;
                    }
                }
            }
            // cout << lesser << here << endl;
            return invs(here);
            // cout << invs(here) << endl;
        };
        while(lo+3<hi) {
            int mid0 = (lo*2+hi)/3;
            int mid1 = (lo+2*hi)/3;
            auto fmid0 = f(mid0), fmid1 = f(mid1);
            if(fmid0<fmid1) {
                lo=mid0;
            } else if(fmid0==fmid1) {
                lo=mid0;
                hi=mid1;
            } else {
                hi=mid1;
            }
        }
        FOR(i, lo, hi+1) bestInvs=max(bestInvs, f(i));
        cout << bestInvs << endl;

    }
    return 0;
}
/*
1
9 3
1 2
3 4
8 9


*/