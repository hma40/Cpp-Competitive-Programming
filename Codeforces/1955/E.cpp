#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
ll mod = 1000000007;
ll inf = 1e15;
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
int times = 0;
struct SegTree {
    int n;
    vector<int> first, last, tree;
    SegTree(int m) {
        n=m;
        while(n!=(n&(-n))) n++;
        first.resize(2*n);
        last.resize(2*n);
        tree.resize(2*n);
        R0F(i, n) {
            first[i+n]=last[i+n]=i;
        }
        ROF(i, 1, n) {
            first[i]=first[2*i];
            last[i]=last[2*i+1];
        }
        // cout << first << " " << last << " " << tree << endl;
    }
    void update(int pos, int i, int amount) {
        // if(times<50) {
        //     times++;
        //     // cout << "line 74: " << pos << " " << i << " " << amount << endl;
        // }
        if(i>=n) {
            tree[i]+=amount;
            return;
        }
        if(first[2*i]<=pos&&last[2*i]>=pos) update(pos, 2*i, amount);
        else update(pos, 2*i+1, amount);
        // if(times<50) {
        //     // cout << "DONE WITH UPDATE " << pos << " " << i << " " << amount << endl;
        //     // cout << tree << endl;
        // }
        tree[i]=tree[2*i]+tree[2*i+1];
    }
    // int change(int left, int right) {
    //     if(times<50) {
    //         times++;
    //         cout << "GOT TO LINE 84 " << endl;
    //     }
    //     update(left, 1, 1);
    //     update(right+1, 1, -1);
    // }
    int query(int left, int right, int i) {
        if(first[i]==left&&last[i]==right) return tree[i];
        int sum = 0;
        if(first[2*i]<=right&&last[2*i]>=left) {
            sum+=query(left, min(right, last[2*i]), 2*i);
        }
        if(first[2*i+1]<=right&&last[2*i+1]>=left) {
            sum+=query(max(left, first[2*i+1]), right, 2*i+1);
        }
        return sum;
    }
    int get(int pos) {
        return query(0, pos, 1);
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        string s;
        cin >> n >> s;
        // cout << n << " " << s << endl;
        ROF(i, 1, n+1) {
            // cout << i << endl;
            SegTree st(n+1);
            // cout << n-i+1 << endl;
            F0R(j, n-i+1) {
                // cout << i << " " << j << endl;
                int times = st.get(j);
                // cout << times << endl;
                if(times%2&&s[j]=='1'||times%2==0&&s[j]=='0') {
                    // cout << "GOT TO LINE 118" << endl;
                    // st.change(j, j+i-1);
                    // if(times<50) {
                    //     cout << "GOT TO END OF LINE 118" << endl;
                    // }   
                    st.update(j, 1, 1);
                    st.update(j+i, 1, -1);
                }
                // cout << "LINE 119" << endl;
            }
            // cout << "GOT TO LINE 120" << endl;
            bool fail = false;
            // cout << i << " " << st.tree << endl;
            FOR(j, n-i+1, n) {
                // cout << "LINE 121 " << i << " " << j << " " << fail << endl;
                int times = st.get(j);
                if(times%2&&s[j]=='1'||times%2==0&&s[j]=='0') {
                    fail=true;
                    break;
                }
            }
            if(!fail) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}
