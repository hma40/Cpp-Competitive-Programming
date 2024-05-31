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
struct SegTree {
    int n;
    vt<int> beg,end,tree,sum;
    void change(int i, int pos, int val) {
        if(i>=n) {
            sum[i]+=val;
            return;
        }
        if(beg[2*i]<=pos&&end[2*i]>=pos) {
            change(2*i, pos, val);
        } else {
            change(2*i+1, pos, val);
        }
        sum[i]=sum[2*i]+sum[2*i+1];
    }
    int su(int i, int L, int R) {
        if(beg[i]==L&&end[i]==R) {
            // cout << "RETURNING " << tree[i] << " FOR " << L << " " << R << endl;
            return sum[i];
        }
        int ans = 0;
        if(beg[2*i]<=R&&end[2*i]>=L) {
            ans+=su(2*i, L, min(end[2*i], R));
        }
        if(beg[2*i+1]<=R&&end[2*i+1]>=L) {
            ans+=su(2*i+1, max(L, beg[2*i+1]), R);
        }
        // cout << "RETURNING " << ans << " FOR " << L << " " << R << endl;
        return ans;
    }
    SegTree(int nn): n(nn) {
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n, -1);
        sum.resize(2*n);
        F0R(i, n) {
            beg[n+i]=end[i+n]=i;
        }
        R0F(i, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
    }
    SegTree(int nn, vt<int> orig): n(nn) {
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n, -1);
        sum.resize(2*n);
        F0R(i, n) {
            beg[n+i]=end[i+n]=i;
        }
        R0F(i, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        F0R(i, nn) {
            tree[i+n]=orig[i];
            sum[i+n]=sum[i];
        }
        ROF(i, 1, n) {
            sum[i]=sum[2*i]+sum[2*i+1];
            tree[i]=max(tree[2*i], tree[2*i+1]);
        }
        // cout << beg << end << endl;
    } 
    int getMax(int i, int L, int R) {
        // cout << "GETMAX CALLED FOR " << i << " " <<  L << " " << R << endl;
        if(beg[i]==L&&end[i]==R) {
            // cout << "RETURNING " << tree[i] << " FOR " << L << " " << R << endl;
            return tree[i];
        }
        int ans = -1;
        if(beg[2*i]<=R&&end[2*i]>=L) {
            ans=max(ans, getMax(2*i, L, min(end[2*i], R)));
        }
        if(beg[2*i+1]<=R&&end[2*i+1]>=L) {
            ans=max(ans, getMax(2*i+1, max(L, beg[2*i+1]), R));
        }
        // cout << "RETURNING " << ans << " FOR " << L << " " << R << endl;
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        vt<int> score(s.size()+1);
        F0R(i, s.size()) {
            if(s[i]=='(') {
                score[i+1]=score[i]+1; 
            } else {
                score[i+1]=score[i]-1;
            }
        }
        SegTree st(score.size(), score);
        // cout << st.tree << endl;
        vt<vt<int>> queries;
        F0R(i, s.size()) {
            if(score[i]==0) continue;
            int lo = i+1;
            int hi = s.size()+1;
            int noOver = score[i]*2;
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                // cout << mid << " " << st.getMax(1, i+1, mid) << endl;
                if(st.getMax(1, i+1, mid)<=noOver) {
                    lo=mid;
                } else {
                    hi=mid;
                }
            }
            if(st.getMax(1,i+1,hi)>noOver) {
                queries.add({score[i], i+1, lo, 1});
                queries.add({score[i]-1, i+1, lo, -1});
            } else {
                queries.add({score[i],i+1,hi, 1});
                queries.add({score[i]-1, i+1, lo, -1});
            }
        }

        // cout << queries << endl;
        // cout << score << endl;
        vt<pair<int, int>> ts;
        F0R(i, score.size()) {
            ts.add({score[i], i});
        }
        ts.add({inf, 0});
        sort(begin(ts),end(ts));
        sort(begin(queries),end(queries));
        int ans = 0;
        int tI = 0;
        SegTree stst(score.size()+1);
        trav(x, queries) {
            // cout << x << endl;
            while(ts[tI].f<=x[0]) {
                stst.change(1, ts[tI].s, 1);
                tI++;
            }
            ans+=x[3]*stst.su(1, x[1], x[2]);
            // cout << x << " " << ans << endl;
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
((()))
0 1 2 3 2 1 0
*/