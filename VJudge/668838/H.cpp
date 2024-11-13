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
struct Team {
    int solves;
    int teamNumber;
    int penalty;
    vt<int> ACPenalty;
    map<int,int> wrongSubs;
    set<int> firstAC;
    // map<int,int> firstAC;
    Team(int n) {
        solves=0;
        penalty=0;
        ACPenalty.clear();
        wrongSubs.clear();
        firstAC.clear();
        teamNumber=n;
    }
};
void print(Team &t, int place) {
    string s = "";
    s+=to_string(place);
    while(s.size()<4)s+=' ';
    s+=to_string(t.teamNumber);
    while(s.size()<8) s+=' ';
    F0R(i, 3-(to_string(t.solves)).size()) s+=' ';
    s+=to_string(t.solves);
    F0R(i, 5-(to_string(t.penalty)).size()) s+=' ';
    s+=to_string(t.penalty);
    cout << s << endl;
}
bool equal(Team &a, Team &b) {
    return a.solves==b.solves && a.penalty==b.penalty && a.ACPenalty==b.ACPenalty;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/a.txt" , "w", stdout);
    int nt, np, ns, nr;
    cin >> nt >> np >> ns >> nr;
    vt<Team> teams;
    F0R(i, nt) {
        teams.add(Team(i+1));
    }
    vt<array<int,4>> data(ns);
    F0R(i, ns) {
        cin >> data[i][0] >> data[i][1] >> data[i][2] >> data[i][3];
        data[i][0]--;
    }
    F0R(i, ns) {
        if(data[i][2]>=300) continue;
        if(data[i][3]==1) {
            if(teams[data[i][0]].firstAC.count(data[i][1])) continue;
            teams[data[i][0]].penalty+=data[i][2]+20*teams[data[i][0]].wrongSubs[data[i][1]];
            teams[data[i][0]].ACPenalty.add(data[i][2]+20*teams[data[i][0]].wrongSubs[data[i][1]]);
            teams[data[i][0]].firstAC.insert(data[i][1]);
            teams[data[i][0]].solves++;
        } else {
            teams[data[i][0]].wrongSubs[data[i][1]]++;
        }
    }
    // trav(x, teams) {
        // cout << x.solves << " " << x.penalty << " " << x.ACPenalty << " " << x.teamNumber << endl;
    // }
    sort(begin(teams),end(teams), [](const auto a, const auto b)->bool{
        if(a.solves!=b.solves) return a.solves>b.solves;
        if(a.penalty!=b.penalty) return a.penalty<b.penalty;
        R0F(i, a.solves) {
            if(a.ACPenalty[i]!=b.ACPenalty[i]) {
                return a.ACPenalty[i]<b.ACPenalty[i];
            }
        }
        return a.teamNumber<b.teamNumber;
    });
    // trav(x, teams) {
    //     cout << x.solves << " " << x.penalty << " " << x.ACPenalty << " " << x.teamNumber << endl;
    // }
    int last = 0;
    F0R(i, nt) {
        if(i<nr||equal(teams[i], teams[nr-1])) {
            if(i==0||!equal(teams[i], teams[i-1])) {
                last=i+1;
            }
            print(teams[i], last);
            // if(equal(teams[n-i-1], teams[n-i]))
        }
    }
    return 0;
}
/*
27 29 50
*/