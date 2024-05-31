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
vt<int> fakeSolve(int n, int m, vt<int> a, vt<int> b) {
    int progEnd = inf, testEnd = inf, progEndSpec = inf, testEndSpec = inf;
    int pCount = 0, tCount = 0;
    if(n==0) {
        progEnd=-1;
    } 
    if(m==0) {
        testEnd=-1;
    }
    F0R(i, n+m+1) {
        if(a[i]>b[i]) pCount++;
        else tCount++;
        // cout << i << " " << pCount << " " << tCount << endl;
        if(pCount==n&&progEnd==inf) progEnd=i;
        if(pCount==n+1&&progEndSpec==inf) progEndSpec=i;
        if(tCount==m&&testEnd==inf) testEnd=i;
        if(tCount==m+1&&testEndSpec==inf) testEndSpec=i;
    }
    vt<int> likePref(n+m+2), progPref(n+m+2), testPref(n+m+2);
    FOR(i, 0, n+m+1) {
        likePref[i+1]=likePref[i]+max(a[i], b[i]);
        progPref[i+1]=progPref[i]+a[i];
        testPref[i+1]=testPref[i]+b[i];
    }
    cout << "LINE 81 " << testEnd << " " << progEnd << " " << testEndSpec << " " << progEndSpec << endl;
    vt<int> ans(n+m+1);
    // cout << likePref << progPref << testPref << endl;
    if(progEnd==testEnd&&progEnd==inf) {
        // assert(pCount<n&&tCount<m);
        // cout << -1 << endl;
        // return 0;
    }
    F0R(i, n+m+1) {

        if(progEnd>testEnd) {
            if(i>testEnd) {
                // cout << "CASE 1" << endl;
                ans[i]=likePref[testEnd+1]+progPref.back()-progPref[testEnd+1]-a[i];
                continue;
            } 
        } else {
            if(i>progEnd) {
                // cout << "CASE 2" << endl;
                ans[i]=likePref[progEnd+1]+testPref.back()-testPref[progEnd+1]-b[i];
                continue;
            }
        }
        if(a[i]>b[i]) {
            if(progEndSpec==testEnd) {
                ans[i]=likePref[testEnd+1]-max(a[i],b[i]);
            }
            if(progEndSpec>testEnd) {
                // cout << "CASE 3" << endl;
                // cout << progPref.back() << " " << progPref[testEnd+1] << " " << likePref[testEnd+1] << " " << a[i] << endl;
                ans[i]=likePref[testEnd+1]+progPref.back()-progPref[testEnd+1]-max(a[i], b[i]);
            } else {
                // cout << "CASE 4" << endl;
                ans[i]=likePref[progEndSpec+1]+testPref.back()-testPref[progEndSpec+1]-max(a[i], b[i]);
            }
        } else {
            // if(testEndSpec)
            if(testEndSpec==progEnd) {
                ans[i]=likePref[testEnd+1]-max(a[i],b[i]);
            }
            if(testEndSpec>progEnd) {
                // cout << "CASE 5" << endl;
                ans[i]=likePref[progEnd+1]+testPref.back()-testPref[progEnd+1]-max(a[i], b[i]);
            } else {
                // cout << "CASE 6" << endl;
                // cout << testEndSpec << endl;
                ans[i]=likePref[testEndSpec+1]+progPref.back()-progPref[testEndSpec+1]-max(a[i], b[i]);
            }
        }
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    while(true) {
        int n = rand()%10, m = rand()%10;
        vt<int> a(n+m+1),b(n+m+1);
        F0R(i, n+m+1) a[i]=rand()%100;
        F0R(i, n+m+1) b[i]=rand()%100;
        F0R(i, n+m+1) {
            while(a[i]==b[i]) {
                a[i]=rand()%100;
                b[i]=rand()%100;
            }
        }
        cout << n << " " << m << " " << a << " " << b << endl;
        cout << fakeSolve(n,m,a,b) << endl;
    }
    return 0;
}