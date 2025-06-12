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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        string s;
        int a,b,ab,ba;
        cin >> s >> a >> b >> ab >> ba;
        vt<int> saea, saeb, sbea, sbeb;
        string cur;
        cur+=s[0];
        FOR(i, 1, s.size()) {
            if(s[i]==s[i-1]) {
                if(cur[0]=='A'&&cur.back()=='A') saea.add(cur.size());
                else if(cur[0]=='A'&&cur.back()=='B') saeb.add(cur.size());
                else if(cur[0]=='B'&&cur.back()=='A') sbea.add(cur.size());
                else sbeb.add(cur.size());
                while(cur.size()) cur.pop_back();
                cur+=s[i];
            } else {
                cur+=s[i];
            }
        }
        if(cur[0]=='A'&&cur.back()=='A') saea.add(cur.size());
        else if(cur[0]=='A'&&cur.back()=='B') saeb.add(cur.size());
        else if(cur[0]=='B'&&cur.back()=='A') sbea.add(cur.size());
        else sbeb.add(cur.size());
        // cout << saea << " " << saeb << " " << sbea << " " << sbeb << endl;
        /*
        ab...ab -> a + b + ba...ba
        */
        sort(rbegin(saeb), rend(saeb));
        sort(rbegin(sbea), rend(sbea));
        while(ab&&saeb.size()) {
            ab--;
            saeb.back()-=2;
            if(saeb.back()==0) saeb.pop_back();
        }
        // cout << saea << " " << saeb << " " << sbea << " " << sbeb << " " << a << " " << b << " " << ab << " " << ba << endl;
        while(ba&&sbea.size()) {
            ba--;
            sbea.back()-=2;
            if(sbea.back()==0) sbea.pop_back();
        }
        // cout << saea << " " << saeb << " " << sbea << " " << sbeb << " " << a << " " << b << " " << ab << " " << ba << endl;
        /*
        baba...ba
        b + ab...ab + a
        */
        while(ab&&sbea.size()) {
            a--;
            b--;
            sbea.back()-=2;
            while(ab&&sbea.back()) {
                ab--;
                sbea.back()-=2;
            }
            if(sbea.back()==0) sbea.pop_back();
        }
        // cout << saea << " " << saeb << " " << sbea << " " << sbeb << " " << a << " " << b << " " << ab << " " << ba << endl;
        while(ba&&saeb.size()) {
            a--;
            b--;
            saeb.back()-=2;
            while(ba&&saeb.back()) {
                ba--;
                saeb.back()-=2;
            }
            if(saeb.back()==0) saeb.pop_back();
        }
        ab+=ba;
        /*
        abab...aba = abab... + a + baba...
        */
        while(ab&&saea.size()) {
            a--;
            saea.back()--;
            while(ab&&saea.back()) {
                ab--;
                saea.back()-=2;
            }
            if(saea.back()==0) saea.pop_back();
        }
        while(ab&&sbeb.size()) {
            b--;
            sbeb.back()--;
            while(ab&&sbeb.back()) {
                ab--;
                sbeb.back()-=2;
            }
            if(sbeb.back()==0) sbeb.pop_back();
        }
        while(saea.size()) {
            a-=(saea.back()+1)/2;
            b-=(saea.back())/2;
            saea.pop_back();
        }
        while(sbeb.size()) {
            a-=(sbeb.back())/2;
            b-=(sbeb.back()+1)/2;
            sbeb.pop_back();
        }
        while(saeb.size()) {
            a-=saeb.back()/2;
            b-=saeb.back()/2;
            saeb.pop_back();
        }
        while(sbea.size()) {
            a-=sbea.back()/2;
            b-=sbea.back()/2;
            sbea.pop_back();
        }
        if(a>=0&&b>=0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
/*
BABABABABABABABA
A
ABABABAB
BABA
A
A
A
AB
B
B
5 6 6 7

1
BABABABABABABABAAABABABABBABAAAAABBB
5 6 6 7

bababa
*/