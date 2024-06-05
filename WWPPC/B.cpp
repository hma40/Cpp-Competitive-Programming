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
vt<int> fib;
vt<int> precomp(100001);
int solve(int y) {
    int ans = 0;
    int index = fib.size()-1;
    while(y) {
        // cout << y << " " << ans << " " << index << " " << fib[index] << endl;
        // cout.flush();
        while(y>=fib[index]) {
            y-=fib[index];
            ans++;
        }
        index--;
    }
    return ans;
}
int range(int x, int y, int index) {
    // cout << "RANGE CALLED FOR " << x << " " << y << endl;
    if((x==0||x==1)&&y<100001) {
        // cout << "CASE 0: RETURNING " << x << " " << y << " " << precomp[x] << endl;
        return precomp[y];
    } 
    while(fib[index]>y) index--;
    // cout << x << " " << y << " " << fib[index] << endl;
    if(fib[index]<=x) {
        // cout << "CASE 1 REACHED FOR " << x << " " << y << endl;
        int ans = (y-x+1+range(x-fib[index], y-fib[index], index))%mod;
        // cout << "CASE 1: RETURNING " << x << " " << y << " " << ans << endl;
        return ans;
    } else {
        // cout << "CASE 2 REACHED FOR " << x << " " << y << endl;
        // cout << "RETURNING " << (y-fib[index]+1+range(x,fib[index]-1,index)+range(0,y-fib[index],index))%mod << " FOR " << x << " " << y << endl;
        int ans = (y-fib[index]+1+range(x,fib[index]-1,index)+range(0,y-fib[index],index))%mod;
        // cout << "CASE 2: RETURNING " << x << " " << y << " " << ans << endl;
        return ans;
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    fib.add(1);
    fib.add(1);
    while(fib.back()<inf) {
        fib.add(fib.back()+fib[fib.size()-2]);
    }
    // cout << fib.size() << endl;
    // int t;
    // cin >> t;
    FOR(i, 1, precomp.size()) {
        precomp[i]=precomp[i-1]+solve(i);
        precomp[i]%=mod;
    }
    // cout << precomp[4] << endl;
    int t;
    cin >> t;
    while(t--) {
        int x,y;
        cin >> x >> y;
        cout << range(x,y,fib.size()-1) << endl;
    }
    return 0;
}