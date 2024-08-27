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
#define vt vector
#define endl "\n"
#define int long long
#define double long double
ll mod = 998244353;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
class BIT {
  private:
	int size;
	vector<int> bit;

  public:
	BIT(int size) : size(size), bit(size + 1) {}

	/** Adds val to the element at index ind. */
	void add(int ind, int val) {
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] += val; }
	}

	/** @return The sum of all values in [0, ind]. */
	int pref_sum(int ind) {
		ind++;
		int total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}
    int sum(int l, int r) {
        if(l==0) return pref_sum(r);
        return pref_sum(r)-pref_sum(l-1);
    }
};    
int ans[200001][41];
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;

    while(t--) {
        int n,k;
        cin >> n >> k;
        vt<int> p(n);
        F0R(i, n) cin >> p[i];
        vt<int> q(k);
        F0R(i, k) cin >> q[i];
        stack<array<int,3>> pq;
        F0R(i, n) {
            FOR(j, 1, 21) {
                if((p[i]/(1LL<<j))==0) {
                    ans[i][20-j]=0;
                } else {
                    pq.push({p[i]/(1LL<<j), i, 20-j});
                }
            }
            // queries.add({i, p[i], 20});
            pq.push({p[i], i, 20});
            FOR(j, 1, 21) {
                if((p[i]*(1LL<<j))>=2*n) {
                    ans[i][20+j]=n-1-i;
                } else {
                    pq.push({p[i]*(1LL<<j), i, 20+j});
                }
            }
        }
        // cout << pq << endl;
        // assert(false);
        // cout << pq << endl;
        BIT st(n*2);
        R0F(i, n) {
            while(pq.size()&&pq.top()[1]==i) {
                auto bruh = pq.top();
                pq.pop();
                ans[i][bruh[2]]=st.pref_sum(bruh[0]);
            }
            st.add(p[i], 1);
        }
        // assert(false);
        ll an = 0;
        st=BIT(k);
        F0R(i, k) {
            an+=st.sum(q[i]+1, k-1);
            an%=mod;
            st.add(q[i], 1);
        }
        // cout << "LINE 215 " << an << endl;
        an*=n;
        an%=mod;
        // cout << an << endl;
        vt<int> count(41);
        FOR(diff, 1-k, k) {
            //how many are there?
            int bruh = abs(diff);
            //0 diff, 1 diff+1, ..., k-diff-1, k-1
            int hr = k-bruh;
            //which bucket does this fit into?
            if(abs(diff)>20) {
                if(diff<0) {
                    count[40]+=hr;
                    count[40]%=mod;
                } else {

                }
            } else {
                count[diff+20]+=hr;
                count[diff+20]%=mod;
            }
        }
        // cout << "LINE 252 " << an << endl;
        F0R(i, n) {
            F0R(j, 41) {
                an+=(ll)ans[i][j]*count[j];
                // if(ans[i][j]*count[j]!=0) {
                    // cout << "LINE 257 " << i << " " << j << " " << ans[i][j] << " " << count[j] << endl;
                // }
                an%=mod;
            }
        }
        cout << an << endl;
    }   
    return 0;
}
/*
5*3=15
2*1+1*1+1*2+1*2+
*/