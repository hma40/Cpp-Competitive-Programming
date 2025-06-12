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
struct SegTree {
    int n;
    vt<int> maxTree, minTree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        maxTree.resize(2*np, -inf);
        minTree.resize(2*np, inf);
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            maxTree[i+n]=arr[i];
            minTree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            maxTree[i] = max(maxTree[2*i], maxTree[2*i+1]);
            minTree[i] = min(minTree[2*i], minTree[2*i+1]);
        }
    }
    void set(int pos, int x) {
        pos+=n;
        maxTree[pos]=x;
        minTree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            maxTree[pos] = max(maxTree[2*pos], maxTree[2*pos+1]);
            minTree[pos] = min(minTree[2*pos], minTree[2*pos+1]);
        }
    }
    int getMax(int a, int b) {
        a+=n;
        int ans = -inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=max(ans, maxTree[a++]);
            if(b%2==0) ans=max(ans, maxTree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
    int getMin(int a, int b) {
        a+=n;
        int ans = inf;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans=min(ans, minTree[a++]);
            if(b%2==0) ans=min(ans, minTree[b--]);
            a/=2;
            b/=2;
        }
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n);
        F0R(i, n) cin >> a[i];
        vt<int> leftGreater(n, -1), leftLesser(n, -1), rightGreater(n, n), rightLesser(n, n);
        vt<int> st;
        F0R(i, n) {
            while(st.size() && a[st.back()]<a[i]) {
                rightGreater[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }
        st.clear();
        F0R(i, n) {
            while(st.size() && a[st.back()]>a[i]) {
                rightLesser[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }
        st.clear();
        R0F(i, n) {
            while(st.size() && a[st.back()]>a[i]) {
                leftLesser[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }
        st.clear();
        R0F(i, n) {
            while(st.size() && a[st.back()]>a[i]) {
                leftGreater[st.back()]=i;
                st.pop_back();
            }
            st.push_back(i);
        }
        //has to exist M so that everything before is either prefix min or prefix max, and everything after is either suffix min or suffix max
        //Let's fix this M and calculate L and R.
        //for R for example, if there exists i>M and a[i]>a[M] and j = leftGreater[i], then it cannot go up to i
        // similarly, if there exiss i>M and a[i]<a[M] and j = leftLesser[i], then it cannot go up to i
        // process the permutation in increasing order? 
        vt<int> right(n);
        min_pq<pair<int,int>> pq;
        F0R(i, n) pq.push({a[i],i});

    }
    return 0;
}