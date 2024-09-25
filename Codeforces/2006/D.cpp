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
#define vt vector
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int poss(vt<int> &need, vt<int> &have, int equalSqr, int changes) {
    int haveSum=changes, needSum=0;
    int problemHave=-1;
    F0R(i, need.size()) {
        haveSum+=have[i];
        if(changes>=need[i]) {
            changes-=need[i];
        } else {
            needSum+=need[i]-changes;
            changes=0;
        }
        if(haveSum+1<needSum) return false;
        if(haveSum<needSum&&problemHave==-1) problemHave=haveSum;
    }
    if(problemHave==-1) return true;
    else if(haveSum!=problemHave) return false;
    else if(equalSqr!=0) return false;
    else return true;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n,q,k;
        cin >> n >> q >> k;
        int sqr = 1;
        while(sqr*sqr<=k) sqr++;
        // vt<vt<int>> freqPref(n+1, vt<int>(sqr));
        // vt<vt<int>> needPref(n+1, vt<int>(sqr));
        // cout << freqPref << endl;
        sqr--;
        vt<int> arr(n);
        F0R(i, n) {
            cin >> arr[i];
        }
        vt<int> curNeed(sqr+1), curHave(sqr+1);
        vt<array<int,3>> queries(q);
        F0R(i, q) {
            cin >> queries[i][0] >> queries[i][1];
            queries[i][2]=i;
            queries[i][0]--;
            queries[i][1]--;
        }
        vt<int> ans(q);
        sort(begin(queries),end(queries), [](const auto a, const auto b)->bool{
            if(a[0]/300==b[0]/300) {
                return a[1]<b[1];
            } else {
                return a[0]/300<b[0]/300;
            }
        });
        // cout << queries << endl;
        int left=0, right=-1;
        trav(x, queries) {
            while(right<x[1]) {
                right++;
                if(arr[right]>sqr) {
                    curNeed[k/arr[right]]++;
                } else {
                    curHave[arr[right]]++;
                }
            }
            while(right>x[1]) {
                if(arr[right]>sqr) {
                    curNeed[k/arr[right]]--;
                } else {
                    curHave[arr[right]]--;
                }
                right--;
            } 
            while(left<x[0]) {
                if(arr[left]>sqr) {
                    curNeed[k/arr[left]]--;
                } else {
                    curHave[arr[left]]--;
                }
                left++;
            }
            while(left>x[0]) {
                left--;
                if(arr[left]>sqr) {
                    curNeed[k/arr[left]]++;
                } else {
                    curHave[arr[left]]++;
                }
            }
            int exact = 0;
            if(sqr*sqr==k) {
                exact=curHave[sqr];
                curHave[sqr]=0;
            }
            int totHave=0, totNeed=0;
            F0R(i, sqr+1) {
                totHave+=curHave[i];
                // tot+=curHave[i]+curNeed[i];
                totNeed+=curNeed[i];
            }
            int changes = 0;
            if(exact==0) {
                int minHave = (totHave+totNeed)/2;
                changes=max(0, minHave-totHave);
                int lleft=changes;
                int haveSum=changes, needSum=0;
                F0R(i, sqr) {
                    haveSum+=curHave[i];
                    if(lleft>=curNeed[i]) {
                        lleft-=curNeed[i];
                    } else {
                        needSum+=curNeed[i]-lleft;
                        lleft=0;
                    }
                    if(haveSum+1<needSum) {
                        //definitely need more changes
                        //need haveSum>=needSum
                        int minHaveSum = (haveSum+needSum+1)/2;
                        changes+=minHaveSum-haveSum;
                        needSum=(haveSum+needSum)-minHaveSum;
                        haveSum=minHaveSum;
                    } else if(haveSum+1==needSum&&haveSum+needSum!=totHave+totNeed) { 
                        int minHaveSum = (haveSum+needSum+1)/2;
                        changes+=minHaveSum-haveSum;
                        needSum=(haveSum+needSum)-minHaveSum;
                        haveSum=minHaveSum;                       
                    }
                }
                ans[x[2]]=changes;
            } else {
                int minHave = (totHave+totNeed+1)/2;
                changes=max(0, minHave-totHave);
                int lleft=changes;
                int haveSum=changes, needSum=0;
                F0R(i, sqr) {
                    haveSum+=curHave[i];
                    if(lleft>=curNeed[i]) {
                        lleft-=curNeed[i];
                    } else {
                        needSum+=curNeed[i]-lleft;
                        lleft=0;
                    }
                    if(haveSum<needSum) {
                        //definitely need more changes
                        //need haveSum>=needSum
                        int minHaveSum = (haveSum+needSum+1)/2;
                        changes+=minHaveSum-haveSum;
                        needSum=(haveSum+needSum)-minHaveSum;
                        haveSum=minHaveSum;
                    } 
                }
                ans[x[2]]=changes;
            }
            if(sqr*sqr==k) {
                curHave[sqr]=exact;
            }
        }
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}