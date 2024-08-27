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
// #define int long long
#define vt vector
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e9;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());      
int n,k;
vt<vt<int>> notake;
vt<vt<int>> score;
// vt<map<int,int>> atLeast;
bool enough(int i, int aimScore) {
    // cout << i << " " << aimScore << endl;
    int target = k;
    if(i<30) {
        target=min(target, 1<<i);
    }
    int count = 0;
    if(score[0][i]>=aimScore) count=1;
    for(int j = 0; j < i; j++) {
        int scoreHere = aimScore-score[j+1][i];
        trav(x, notake[j]) {
            // cout << j << " " << aimScore << " " << scoreHere << " " << x << " " << count << endl;
            if(-x>=scoreHere) {
                count++;
            } else {
                break;
            }
            if(count>=target) return true;
        }
    }
    // cout << "LINE 152 " << i << " " << aimScore << " " << count << " " << target << endl;
    // return count>=target;
    return false;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n >> k;
        multiset<int> take;
        notake.assign(n, vt<int>());
        // take.assign(n, multiset<int>());
        score.assign(n, vt<int>(n,0));
        // atLeast.assign(n, map<int,int>());
        F0R(i, n) {
            FOR(j, i, n) {
                cin >> score[i][j];
            }
        }
        notake[0].add(0);
        // atLeast[0][0]=1;
        take.insert(score[0][0]);
        FOR(i, 1, n) {
            // cout << "LINE 181 " << i << endl;
            //fill notake 
            multiset<int> temptake;
            trav(x, notake[i-1]) {
                notake[i].add(x);
            }
            trav(x, take) {
                notake[i].add(-x);
            }
            sort(begin(notake[i]), end(notake[i]));
            while(notake[i].size()>k) {
                // notake[i].erase(notake[i].find(*(notake[i].rbegin())));
                notake[i].pop_back();
            }
            // assert(false);
            int lo = -1e9, hi = 1e9+1;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(enough(i, mid)) {
                    lo=mid; 
                } else {
                    hi=mid;
                }
            }
            // assert(false);
            // cout << i << " " << lo << endl;
            for(int j = 0; j < i; j++) {
                trav(x, notake[j]) {
                    // cout << "LINE 201 " << x << " " << score[j+1][i] << endl;
                    if(-x+score[j+1][i]<=lo) break;
                    temptake.insert(-x+score[j+1][i]);
                }
            }
            int target = k;
            if(i<30) {
                target=min(target, 1<<i);
            }      
            if(score[0][i]>=lo&&temptake.size()<=target) {
                // cout << "GOT HERE" << endl;
                temptake.insert(score[0][i]);
            }
            while(temptake.size()<target) {
                temptake.insert(lo);
            }
            swap(take, temptake);
            // cout << i << take << endl;
        }
        vt<int> all;
        trav(x, notake.back()) all.add(-x);
        trav(x, take) all.add(x);
        sort(begin(all),end(all));
        // cout << notake << endl << take << endl;
        F0R(i, k) {
            // cout << *(all.rbegin()) << endl;
            cout << all[all.size()-i-1] << " ";
        }
        cout << endl;
    }
    return 0;
}
/*
1
2 4
0 -6
-7
*/