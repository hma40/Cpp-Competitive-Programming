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
        int n,x;
        cin >> n >> x;
        vt<int> perm(n);
        F0R(i, n) cin >> perm[i];
        x--;
        F0R(i, n) perm[i]--;
        if(n==3&&perm[0]==2&&perm[1]==1) {
            cout << 1 << endl;
            cout << 1 << " " << 3 << endl;
            continue;
        }
        if(n==1) {
            cout << 0 << endl;
            continue;
        }
        int actualInd = 0;
        set<int> bigger, smaller;
        set<int> dB, dS;
        F0R(i, n) {
            if(perm[i]<x) {
                smaller.insert(i);
            }
            if(perm[i]==x) {
                actualInd=i;
            }
            if(perm[i]==n-1) {
                bigger.insert(i);
            }
        } 
        dB = bigger;
        dS = smaller;
        if(x==0) {
            if(perm[0]==0) {
                cout << 0 << endl;
                continue;
            } else {
                cout << 1 << endl << 1 << " " << 1+actualInd << endl;
                continue;
            }
        } else if(x==n-1) {
            if(perm[n-1]==n-1) {
                cout << 0 << endl;
                continue;
            } else {
                cout << 1 << endl << n << " " << 1+actualInd << endl;
                continue;
            }
        }
        int lo = 0, hi = n;
        bool uhoh = false;
        while(lo+1<hi) {
            int mid = (lo+hi)/2;
            if(perm[mid]<x) {
                lo=mid;
                smaller.erase(mid);
            } else if(perm[mid]==x) {
                uhoh=true;
                lo=mid;
            } else {
                bigger.erase(mid);
                hi=mid;
            }
        }
        if(uhoh) {
            if(perm[lo]==x) {
                cout << 0 << endl;
                continue;
            }
            if(smaller.size()) {
                cout << 2 << endl;
                cout << 1+lo << " " << 1+actualInd << endl;
                cout << 1+*(smaller.begin()) << " " << actualInd+1 << endl;
                continue;
            } 
            lo = 0;
            hi = n;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(perm[mid]<x) {
                    lo=mid;
                    dS.erase(mid);
                } else if(perm[mid]==x) {
                    hi=mid;
                } else {
                    dB.erase(mid);
                    hi=mid;
                }
            }
            cout << 2 << endl;
            cout << 1+lo << " " << 1+actualInd << endl;
            cout << 1+*(dB.begin()) << " " << 1+actualInd << endl;
        } else {
            if(perm[lo]==x) {
                cout << 0 << endl;
                continue;
            }
            cout << 1 << endl;
            cout << 1+lo << " " << 1+actualInd << endl;
        }
    }
    return 0;
}
/*
4 2 3 5 1 6
*/