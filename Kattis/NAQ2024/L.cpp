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
// #define endl "\n"
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
FastMod fs(mod);
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);

    int r,c;
    cin >> r >> c;
    vt<string> board(r);
    F0R(i, r) cin >> board[i];
    int leng = 0;
    while(leng<10) {
        bool find = false;
        F0R(i, r) {
            F0R(j, c) {
                if(board[i][j]=='0'+leng) {
                    leng++;
                    find=true;
                }
            }
        }
        if(!find) break;
    }
    while(true) {
        bool find = false;
        F0R(i, r) {
            F0R(j, c) {
                if(board[i][j]=='a'+leng-10) {
                    leng++;
                    find=true;
                }
            }
        }
        if(!find) break;
    }
    pair<int,int> start;
    F0R(i, r) {
        F0R(j, c) {
            if(board[i][j]=='0') {
                start={i,j};
            }
        }
    }
    if(leng==1) {
        cout << 1 << endl;
        return 0;
    }
    if(leng==2) {
        if(r>1&&c>1) {
            cout << 1 << endl;
            return 0;
        }
        string l = "";
        F0R(i, r) {
            F0R(j, c) {
                if(board[i][j]!='.') l+=board[i][j];
            }
        }
        if(l=="A10"||l=="01A") cout << 0 << endl;
        else cout << 1 << endl;
        return 0;
    }
    vt<vt<int>> time(r, vt<int>(c));
    F0R(i, r) {
        F0R(j, c) {
            if(board[i][j]=='.'||board[i][j]=='A') {
                time[i][j]=0;
            } else if(board[i][j]>='0'&&board[i][j]<='9') {
                time[i][j]=leng-board[i][j]+'0';
            } else {
                time[i][j]=leng-board[i][j]+'a'-10;
            }
        }
    }
    map< pair< pair<int,int>,vt<vt<bool>>>, int> mp;
    vt<vt<bool>> beg(r, vt<bool>(c));
    beg[start.f][start.s]=true;
    mp[{{start.f, start.s}, beg}]=0;
    queue<pair< pair<int,int>,vt<vt<bool>>>> q;
    q.push({{start.f, start.s}, beg});
    vt<vt<bool>> visited(r, vt<bool>(c));
    vt<int> dx = {-1,1,0,0}, dy = {0,0,-1,1};
    int iterations = 0;
    bool found = false;
    while(q.size()) {
        iterations++;
        if(iterations%1==0) {
            // cout << q.front() << " " << iterations << endl;
        }
        auto loc = q.front().f;
        auto vis = q.front().s;
        if(board[loc.f][loc.s]!='.'&&board[loc.f][loc.s]!='0') {
            found=true;
            break;
        }
        visited[loc.f][loc.s]=true;
        int dist = mp[q.front()];
        q.pop();
        F0R(i, 4) {
            pair<int,int> nl = {loc.f+dx[i], loc.s+dy[i]};
            if(nl.f<0||nl.s<0||nl.f>=r||nl.s>=c) continue;
            if(vis[nl.f][nl.s]) continue;
            if(dist+1<time[nl.f][nl.s]) continue;
            vis[nl.f][nl.s]=true;
            if(mp.count({nl,vis})) {
                vis[nl.f][nl.s]=false;
                continue;
            }
            mp[{nl, vis}]=dist+1;
            q.push({nl, vis});
            vis[nl.f][nl.s]=false;
        }
    }
    // cout << visited << endl;
    cout << found << endl;
    return 0;
}
/*
1 3
A10

expects 0
*/