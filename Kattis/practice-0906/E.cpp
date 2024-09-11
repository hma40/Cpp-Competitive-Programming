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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;     
    int board[3][3];
    while(t--) {
        string s;
        cin >> s;
        int pow = 1;
        int b10 = 0;
        R0F(i, s.size()) {
            b10+=(s[i]-'0')*pow;
            pow*=8;
        }
        if(b10&(1<<8)) {
            if(b10&(1<<17)) board[0][0]=1;
            else board[0][0]=2;
        } else board[0][0]=0;
        if(b10&(1<<7)) {
            if(b10&(1<<16)) board[0][1]=1;
            else board[0][1]=2;
        } else board[0][1]=0;
         if(b10&(1<<6)) {
            if(b10&(1<<15)) board[0][2]=1;
            else board[0][2]=2;
        } else board[0][2]=0;   
        if(b10&(1<<5)) {
            if(b10&(1<<14)) board[1][0]=1;
            else board[1][0]=2;
        } else board[1][0]=0;
        if(b10&(1<<4)) {
            if(b10&(1<<13)) board[1][1]=1;
            else board[1][1]=2;
        } else board[1][1]=0;
        if(b10&(1<<3)) {
            if(b10&(1<<12)) board[1][2]=1;
            else board[1][2]=2;
        } else board[1][2]=0;
        if(b10&(1<<2)) {
            if(b10&(1<<11)) board[2][0]=1;
            else board[2][0]=2;
        } else board[2][0]=0;
        if(b10&(1<<1)) {
            if(b10&(1<<10)) board[2][1]=1;
            else board[2][1]=2;
        } else board[2][1]=0;
        if(b10&(1<<0)) {
            if(b10&(1<<9)) board[2][2]=1;
            else board[2][2]=2;
        } else board[2][2]=0;
        int outcome = 3;
        int blank = 0;
        F0R(i, 3) {
            F0R(j, 3) {
                if(board[i][j]==0) blank++;
            }
        }
        if(blank==0) outcome=2;
        if(board[0][0]==board[0][1]&&board[0][0]==board[0][2]) {
            if(board[0][0]==1) outcome=0;
            if(board[0][0]==2) outcome=1;
        }
        if(board[1][0]==board[1][1]&&board[1][0]==board[1][2]) {
            if(board[1][0]==1) outcome=0;
            if(board[1][0]==2) outcome=1;
        }
        if(board[2][0]==board[2][1]&&board[2][0]==board[2][2]) {
            if(board[2][0]==1) outcome=0;
            if(board[2][0]==2) outcome=1;
        }
        if(board[0][0]==board[1][0]&&board[0][0]==board[2][0]) {
            if(board[0][0]==1) outcome=0;
            if(board[0][0]==2) outcome=1;
        }
        if(board[0][1]==board[1][1]&&board[0][1]==board[2][1]) {
            if(board[0][1]==1) outcome=0;
            if(board[0][1]==2) outcome=1;
        }
        if(board[0][2]==board[1][2]&&board[0][2]==board[2][2]) {
            if(board[0][2]==1) outcome=0;
            if(board[0][2]==2) outcome=1;
        }
        if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]) {
            if(board[0][0]==1) outcome=0;
            if(board[0][0]==2) outcome=1;
        }
        if(board[2][0]==board[1][1]&&board[2][0]==board[0][2]) {
            if(board[2][0]==1) outcome=0;
            if(board[2][0]==2) outcome=1;
        }
        if(outcome==0) {
            cout << "X wins" << endl;
        } else if(outcome==1) {
            cout << "O wins" << endl;
        } else if(outcome==2) {
            cout << "Cat's" << endl;
        } else {
            cout << "In progress" << endl;
        }
    }
    return 0;
}