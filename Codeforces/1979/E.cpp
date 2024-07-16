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
        map<pair<int,int>,int> allPoints;
        vt<pair<int,int>> points(n);
        F0R(i, n) cin >> points[i].f >> points[i].s;
        F0R(i, n) allPoints[{points[i].f, points[i].s}]=i;
        vt<int> nextSum(n,-1),nextDiff(n,-1);
        F0R(i,n) {
            if(allPoints.count({points[i].f+d/2, points[i].s+d/2})) nextDiff[i]=allPoints[{points[i].f+d/2,points[i].s+d/2}];
            if(allPoints.count({points[i].f+d/2, points[i].s-d/2})) nextSum[i]=allPoints[{points[i].f+d/2,points[i].s-d/2}];
        }
        map<int,set<pair<int,int>>> sum,diff;
        F0R(i, n) {
            if(nextSum[i]!=-1) {
                sum[points[i].f+points[i].s].insert({points[i].f, i});
            }
            if(nextDiff[i]!=-1) {
                diff[points[i].f-points[i].s].insert({points[i].f, i});
            }
        }
        bool done = false;
        // cout << sum << diff << nextSum << nextDiff << endl;
        F0R(i, n) {
            //try being bottom left corner->sum=sum+d
            auto st = sum[points[i].f+points[i].s+d];
            auto pt = st.lower_bound({points[i].f, 0});
            if(pt!=st.end()) {
                pair<int,int> point = *pt;
                if(point.f+d/2<=points[i].f+d) {
                    cout << i+1 << " " << point.s+1 << " " << nextSum[point.s]+1 << endl;
                    done=true;
                    break;
                }
            }
            st = sum[points[i].f+points[i].s-d];
            pt = st.lower_bound({points[i].f-d, 0});
            if(pt!=st.end()) {
                auto point = *pt;
                if(point.f+d/2<=points[i].f) {
                    cout << i+1 << " " << point.s+1 << " " << nextSum[point.s]+1 << endl;
                    done=true;
                    break;
                }
            }
            st = diff[points[i].f-points[i].s+d];
            pt = st.lower_bound({points[i].f, 0});
            if(pt!=st.end()) {
                auto point = *pt;
                if(point.f+d/2<=points[i].f+d) {
                    cout << i+1 << " " << point.s+1 << " " << nextDiff[point.s]+1 << endl;
                    done=true;
                    break;
                }
            }
            st = diff[points[i].f-points[i].s-d];
            pt = st.lower_bound({points[i].f-d, 0});
            if(pt!=st.end()) {
                auto point = *pt;
                if(point.f+d/2<=points[i].f) {
                    cout << i+1 << " " << point.s+1 << " " << nextDiff[point.s]+1 << endl;
                    done=true;
                    break;
                }
            }
        }
        if(!done) cout << "0 0 0\n";
    }
    return 0;
}