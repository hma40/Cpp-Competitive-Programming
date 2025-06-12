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
const ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<int> sum, maxSum, maxStart, maxEnd, maxPrefixInd;
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
        sum.resize(2*n);
        maxSum.resize(2*n);
        maxStart.resize(2*n);
        maxEnd.resize(2*n);
        maxPrefixInd.resize(2*n);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
            sum[i]=-1;
            maxSum[i]=0;
            maxStart[i]=-1;
            maxEnd[i]=-1;
            maxPrefixInd[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
            sum[i]=sum[2*i]+sum[2*i+1];
            maxSum[i]=0;
            maxStart[i]=-1;
            maxEnd[i]=-1;
            maxPrefixInd[i]=beg[i];
        }
        // cout << beg << end << endl;
    }
    void pointSet(int i, int index, int val) {
        if(i>=n) {
            sum[i]=val;
            maxStart[i]=val;
            maxEnd[i]=val;
            if(val>0) maxSum[i]=val;
            else maxSum[i]=0;
            return;
        }
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        sum[i]=sum[2*i]+sum[2*i+1];
        if(maxStart[2*i]>sum[2*i]+maxStart[2*i+1]) {
            maxPrefixInd[i]=maxPrefixInd[2*i];
        } else {
            maxPrefixInd[i]=maxPrefixInd[2*i+1];
        }
        maxStart[i]=max(maxStart[2*i], sum[2*i]+maxStart[2*i+1]);
        maxEnd[i]=max(maxEnd[2*i+1], sum[2*i+1]+maxEnd[2*i]);
        maxSum[i]=max({maxSum[2*i], maxSum[2*i+1], maxEnd[2*i]+maxStart[2*i+1]});
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    array<int,3> maxPrefix(int index, int left, int right) {
        if(beg[index]==left&&end[index]==right) {
            // cout << "RETURNING " << array<int,3>{sum[index], maxStart[index], maxPrefixInd[index]} << " FOR " << index << " " << left << " " << right << endl;
            return {sum[index], maxStart[index], maxPrefixInd[index]};
        }
        array<int,3> ans = {-inf, -inf,-inf};
        if(beg[2*index]<=right&&end[2*index]>=left) {
            auto x = maxPrefix(2*index, left, min(right, end[2*index]));
            ans[0]=x[0];
            ans[1]=x[1];
            ans[2]=x[2];
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            auto r = maxPrefix(2*index+1, max(left, beg[2*index+1]), right);
            if(ans[0]==-inf) {
                ans=r;
            } else {
                if(ans[1]>ans[0]+r[1]) {
                    
                } else {
                    ans[1]=ans[0]+r[1];
                    ans[2]=r[2];
                }

                ans[0]=ans[0]+r[0];
            }
        }
        // cout << "RETURNING " << ans << " FOR " << index << " " << left << " " << right << endl;
        return ans;
    }
    array<int,3> maxPrefix(int left, int right) {
        return maxPrefix(1, left, right);
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
        cin >> n;
        min_pq<pair<int,int>> pq;
        F0R(i, n) {
            int x;
            cin >> x;
            pq.push({x, i});
        }
        SegTree st(n);
        array<int,3> best = {-inf,-inf,-inf};
        while(pq.size()) {
            auto tp = pq.top();
            vt<int> here;
            while(pq.size()&&pq.top().f==tp.f) {
                here.add(pq.top().s);
                pq.pop();
            }
            // cout << here << endl;
            trav(x, here) st.pointSet(x, 0);
            trav(x, here) {
                auto her = st.maxPrefix(1, x, st.n-1);
                // cout << x << " " << her << endl;
                if(her[1]>best[2]) {
                    best[2]=her[1];
                    best[0]=tp.s;
                    best[1]=her[2];
                }
            }
            trav(x, here) st.pointSet(x, 1);
        }
        cout << best[0]+1 << " " << best[1]+1 << endl;
    }
    return 0;
}
/*
1,4,3,2,5,3,3
1,3,2,5,3,3,4
1,3,2,4,5,3,3
*/