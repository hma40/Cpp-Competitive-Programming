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
#define vt vector
#define endl "\n"
#define int long long
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
struct BinaryTrie {
    vt<int> indices, leftChild, rightChild;
    int nextNum;
    BinaryTrie(int n) {
        indices.resize(32*n);
        leftChild.resize(32*n, -1);
        rightChild.resize(32*n, -1);
        nextNum = 1;
    }
    void insert(int idx, int num) {
        int cur = 0;
        R0F(i, 31) {
            if((num&(1<<i))==0) {
                if(leftChild[cur]==-1) {
                    leftChild[cur]=nextNum++;
                }
                cur=leftChild[cur];
                indices[cur]=idx;
            } else {
                if(rightChild[cur]==-1) {
                    rightChild[cur]=nextNum++;
                }
                cur=rightChild[cur];
                indices[cur]=idx;
            }
        }
    }

    int find(int val, int tol) {
        int ans = -1;
        int cur = 0;
        R0F(i, 31) {
            if((tol&(1<<i))==0) {
                if((val&(1<<i))==0) {
                    if(leftChild[cur]==-1) return ans;
                    cur=leftChild[cur];
                } else {
                    if(rightChild[cur]==-1) return ans;
                    cur=rightChild[cur];
                }
            } else {
                if((val&(1<<i))==0) {
                    if(leftChild[cur]!=-1) ans=max(ans, indices[leftChild[cur]]);
                    if(rightChild[cur]==-1) return ans;
                    cur=rightChild[cur];
                } else {
                    if(rightChild[cur]!=-1) ans=max(ans, indices[rightChild[cur]]);
                    if(leftChild[cur]==-1) return ans;
                    cur=leftChild[cur];
                }
            }
        }
        ans=max(ans,indices[cur]);
        return ans;
    }
};
ll count(vt<int> &val, int tol) {
    BinaryTrie b(val.size());
    int best = -1;
    ll ans = 0;
    F0R(i, val.size()) {
        best=max(best, b.find(val[i], tol));
        ans+=best+1;
        b.insert(i,val[i]);
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        ll k;
        cin >> n >> k;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        int lo = 0, hi = 2e9;
        while(lo<hi) {
            int mid = (lo+hi)/2;
            // cout << lo << " " << hi << " " << mid << endl;
            if(count(v,mid)<k) {
                lo=mid+1;
            } else {
                hi=mid;
            }
        }
        cout << lo << endl;
    }   
    return 0;
}