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
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> tree;
    vt<int> setLazy;
    vt<int> addLazy; 
    //CHANGE THESE!
    int none;
    SegTree(int nn) {
        none=(-6969420);
        n=1;
        while(n<nn) {
            n*=2;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        // cout << beg << end << endl;
    }
    void prop(int i) {
        if(setLazy[i]!=none) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setLazy[i]*(end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setLazy[i]*(end[2*i+1]-beg[2*i+1]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i]!=none) {
            if(setLazy[2*i]!=none) {
                setLazy[2*i]+=addLazy[i];
            } else if(addLazy[2*i]!=none) {
                addLazy[2*i]+=(addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1]!=none) {
                setLazy[2*i+1]+=( addLazy[i]);
            } else if(addLazy[2*i+1]!=none) {
                addLazy[2*i+1]+=(addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]+=addLazy[i]*(end[2*i]-beg[2*i]+1);
            tree[2*i]+=addLazy[i]*(end[2*i]-beg[2*i]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, int val) {
        if(i>=n) {
            tree[i]=val;
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, int val) {
        if(i>=n) {
            tree[i]+=val;
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointAdd(2*i, index, val);
        } else {
            pointAdd(2*i+1, index, val);
        }
        tree[i]=(tree[2*i]+tree[2*i+1]);
    }
    void pointAdd(int index, int val) {
        pointAdd(1, index, val);
    }
    int rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans+=r;
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=val*(end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]+=val*(end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=(tree[2*i]+ tree[2*i+1]);
    }
};
FastMod fs(mod);
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vt<int> str(5001), intel(5001);//st[i] = how many attributes there are of <=i
    int n,m;
    cin >> n >> m;
    vt<vt<int>> dp(m+2, vt<int>(m+1));//dp[i][j] = max points if by the ith point gain, you used j of them on strength
    int points = 0;
    F0R(i, n) {
        int x;
        cin >> x;
        if(x>0) {
            str[x]++;
        } else if(x<0) {
            intel[-x]++;
        } else {
            FOR(ii, 1, 5001) str[ii]+=str[ii-1];
            FOR(ii, 1, 5001) intel[ii]+=intel[ii-1];
            points++;
            
            F0R(strength, points+1) {
                int intelligence = points-strength;
                if(strength>0) {
                    dp[points][strength]=dp[points-1][strength-1]+str[strength-1]+intel[intelligence];
                }
                if(intelligence>0) {
                    dp[points][strength]=max(dp[points][strength], dp[points-1][strength]+str[strength]+intel[intelligence-1]);
                }
            }
            str.assign(5001, 0);
            intel.assign(5001, 0);
        }
    }
    // cout << dp << endl;
    int ans = 0;
    FOR(i, 1, 5001) str[i]+=str[i-1];
    FOR(i, 1, 5001) intel[i]+=intel[i-1];
    F0R(strength, m+1) {
        int intelligence = m-strength;
        ans=max(ans, dp[m][strength]+str[strength]+intel[intelligence]);
    }
    cout << ans << endl;
    return 0;
}