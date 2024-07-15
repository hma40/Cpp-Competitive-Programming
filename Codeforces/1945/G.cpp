#include <bits/stdc++.h>
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
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n,d;
        cin >> n >> d;
        vt<pair<int,int>> children(n);
        F0R(i, n) cin >> children[i].f >> children[i].s;
        multiset<int> firstTime;
        F0R(i, n) {
            firstTime.insert(children[i].f);
        }
        int firstIndex = 0;
        // cout << firstTime << endl;
        priority_queue<vt<int>> pq;
        //priority, -time, index
        vt<vt<int>> wait(d+1);
        int time = 1;
        bool done = false;
        while(time<=d) {
            // cout << time << " " << wait << " " << firstTime << " " << firstIndex << endl;
            trav(x, wait[time]) {
                pq.push({children[x].f, -time, -children[x].s, x});
            }
            if(pq.size()) {
                auto top = pq.top();
                // cout << top << endl;
                if(*(firstTime.rbegin())<top[0]) {
                    //serve this guy instead
                    // cout << "AT TIME " << time << " SERVING CHILD " << top[2] << " WHO WILL RETURN IN TIME " << time-top[1]+1 << endl;
                    pq.pop();
                    if(time-top[2]+1<=d) {
                        wait[time-top[2]+1].add(top[3]);
                    }
                    time++;
                    continue;
                } 
            }
            //serve firstTimer
            // cout << "AT TIME " << time << " SERVING CHILD " << firstIndex << " WHO WILL RETURN IN TIME " << time+children[firstIndex].s+1 << endl;
            firstTime.erase(firstTime.find(children[firstIndex].f));
            if(time+children[firstIndex].s+1<=d) {
                wait[time+children[firstIndex].s+1].add(firstIndex);
            
            }
            firstIndex++;
            if(firstTime.size()==0) {
                done=true;
                break;
            }
            time++;
        }
        if(done) {
            cout << time << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
/*
1
5 7
10 2
15 17
10 1
10 5
8 18
*/