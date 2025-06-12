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
struct Dinic {
	using F = ll; // flow type
	struct Edge { int to; F flo, cap; };
	int N; vt<Edge> eds; vt<vt<int>> adj;
	void init(int _N) { N = _N; adj.resize(N), cur.resize(N); }
	/// void reset() { each(e,eds) e.flo = 0; }
	void ae(int u, int v, F cap, F rcap = 0) { assert(min(cap,rcap) >= 0); 
		adj[u].add((eds).size()); eds.add({v,0,cap});
		adj[v].add((eds).size()); eds.add({u,0,rcap});
	}
	vt<int> lev; vt<vt<int>::iterator> cur;
	bool bfs(int s, int t) { // level = shortest distance from source
		lev = vt<int>(N,-1); F0R(i,N) cur[i] = begin(adj[i]);
		queue<int> q({s}); lev[s] = 0; 
		while (q.size()) { int u = q.front(); q.pop();
			trav(e,adj[u]) { const Edge& E = eds[e];
				int v = E.to; if (lev[v] < 0 && E.flo < E.cap) 
					q.push(v), lev[v] = lev[u]+1;
			}
		}
		return lev[t] >= 0;
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge& E = eds[*cur[v]];
			if (lev[E.to]!=lev[v]+1||E.flo==E.cap) continue;
			F df = dfs(E.to,t,min(flo,E.cap-E.flo));
			if (df) { E.flo += df; eds[*cur[v]^1].flo -= df;
				return df; } // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int s, int t) {
		F tot = 0; while (bfs(s,t)) while (F df = 
			dfs(s,t,numeric_limits<F>::max())) tot += df;
		return tot;
	}
    vt<pair<int,int>> getMinCutEdges() {
        vt<pair<int,int>> cutEdges;
        F0R(u, N) {
            if (lev[u] == -1) continue; 
            trav(idx, adj[u]) {
                if (idx & 1) continue; 
                auto e = eds[idx];
                if (lev[e.to] == -1 && e.flo == e.cap && e.cap > 0) {
                    cutEdges.add({u, e.to});
                }
            }
        }
        return cutEdges;
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
        
    }
    return 0;
}