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
std::istream& operator>>(std::istream& in, __int128_t& num) {
    std::string input;
    in >> input;
    
    num = 0;
    bool isNegative = false;
    size_t i = 0;
    
    if (input[0] == '-') {
        isNegative = true;
        i = 1;
    }
    
    for (; i < input.size(); ++i) {
        num = num * 10 + (input[i] - '0');
    }
    
    if (isNegative) {
        num = -num;
    }

    return in;
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
#define int __int128_t
#define vt vector
#define endl "\n"
#define double long double
ll mod = 1000000007;
int inf = 2e16+1;
int abs(int x) {
    if(x<0) return -x;
    return x;
}
int dist(pair<int,int> a, pair<int,int> b) {
    return abs(a.f-b.f)+abs(a.s-b.s);
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int x0,y0,ax,ay,bx,by,xs,ys,t;
    cin >> x0 >> y0 >> ax >> ay >> bx >> by >> xs >> ys >> t;
    pair<int,int> start = {xs,ys};
    vector<pair<int,int>> places;
    places.add({x0,y0});
    auto prev = places[0];
    while(prev.f<=inf&&prev.s<=inf) {
        places.add({prev.f*ax+bx, prev.s*ay+by});
        prev=places.back();
        prev.f=min(prev.f, 1+inf);
        prev.s=min(prev.s, 1+inf);
    }
    // cout << places << endl;
    places.add({-inf, inf});
    //start from 0
    int ans = 0;
    int distAlr = dist(start, places[0]);
    int ind = 0;
    while(distAlr<=t) {
        ans++;
        distAlr+=dist(places[ind], places[ind+1]);
        ind++;
    }
    FOR(i, 1, places.size()) {
        distAlr = dist(start, places[i]);
        ind = i;
        int here = 0;
        while(ind>0) {
            if(distAlr<=t) {
                here++;
                distAlr+=dist(places[ind], places[ind-1]);
            }
            ind--;
        }
        ans=max(ans, here);
    }
    cout << ans << endl;
    return 0;
}
/*
xs+ys>3e16 = impossible
(1,1)
(2,2)
(4,4)
(8,8)
(16,16)
(32,32)
(64,64)
(128,128)
*/