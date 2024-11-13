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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int queriesLeft = 0;
int query(int x, int y, int z) {
    assert(queriesLeft>0);
    queriesLeft--;
    cout << 2 << " " << 1+x << " " << 1+y << " " << 1+z << endl;
    int an;
    cin >> an;
    return an;
}
vt<int> order(vt<int> x, int sm, int lar) {
    // cout << "ORDER CALLED FOR " << x << " " << sm << " " << lar << endl;
    vt<int> left, mid, right;
    trav(y, x) {
        if(query(sm, y, lar)) {
            mid.add(y);
        } else if(query(y, sm, lar)) {
            left.add(y);
        } else {
            right.add(y);
        }
    }
    // cout << left << mid << right << endl;
    if(left.size()<=1) {
        
    } else if(left.size()==2) {
        if(query(left[1], left[0], sm)) {
            swap(left[0], left[1]);
        }
    } else {
        int f = rnd()%left.size();
        int s = f;
        while(s==f) {
            s = rnd()%left.size();
        }
        f=left[f];
        s=left[s];
        vt<int> temp;
        F0R(i, left.size()) {
            if(left[i]!=f&&left[i]!=s) temp.add(left[i]);
        }
        swap(temp,left);
        if(query(f,s,sm)) {
            //f<s
            left = order(left, f, s);
        } else {
            left = order(left, s, f);
        }
    }
    if(right.size()<=1) {
        
    } else if(right.size()==2) {
        if(query(right[0], right[1], sm)) {
            swap(right[0], right[1]);
        }
    } else {
        int f = rnd()%right.size();
        int s = f;
        while(s==f) {
            s = rnd()%right.size();
        }
        f=right[f];
        s=right[s];
        vt<int> temp;
        F0R(i, right.size()) {
            if(right[i]!=f&&right[i]!=s) temp.add(right[i]);
        }
        swap(temp,right);
        if(query(sm, f,s)) {
            //f<s
            right = order(right, f, s);
        } else {
            right = order(right, s, f);
        }
    } 
    if(mid.size()<=1) {
        
    } else if(mid.size()==2) {
        if(query(mid[1], mid[0], lar)) {
            swap(mid[0], mid[1]);
        }
    } else {
        int f = rnd()%mid.size();
        int s = f;
        while(s==f) {
            s = rnd()%mid.size();
        }
        f=mid[f];
        s=mid[s];
        vt<int> temp;
        F0R(i, mid.size()) {
            if(mid[i]!=f&&mid[i]!=s) temp.add(mid[i]);
        }
        swap(temp,mid);
        if(query(sm, f,s)) {
            //f<s
            mid = order(mid, f, s);
        } else {
            mid = order(mid, s, f);
        }
    } 
    vt<int> ret;
    trav(xx, left) ret.add(xx);
    ret.add(sm);
    trav(xx, mid) ret.add(xx);
    ret.add(lar);
    trav(xx, right) ret.add(xx);
    return ret;
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
        queriesLeft=16*n;
        // int fir = rnd()%n;
        // int sec = fir;
        // while(sec==fir) {
        //     sec=rnd()%n;
        // }
        int fir = rnd()%n;
        int sec = fir;
        while(sec==fir) {
            sec=rnd()%n;
        }
        fir=0;
        sec=2;
        cout << "1 " << fir+1 << " " << sec+1 << endl;
        int comp;
        cin >> comp;
        int smaller,bigger;
        if(comp) {
            smaller=fir;
            bigger=sec;
        } else {
            smaller=sec;
            bigger=fir;
        }
        vt<int> all;
        F0R(i, n) {
            if(i!=smaller&&i!=bigger) all.add(i);
        }
        auto ans = order(all, smaller, bigger);
        // cout << ans << endl;
        vt<int> a(n);
        F0R(i, n) {
            a[ans[i]]=i+1;
        }
        cout << "! " << 1+ans[0];
        FOR(i, 1, n) {
            cout << " " << 1+ans[i];
        }
        cout << endl;
    }   
    return 0;
}
/*
1
4
1 2 4 3
*/