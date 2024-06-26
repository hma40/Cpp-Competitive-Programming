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
ll mod = 1000000007;
ll inf = 1e9+5;
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
    vt<int> beg,end;
    vt<int> tree;
    vt<int> setLazy;
    vt<int> addLazy; 
    //CHANGE THESE!
    int none;
    int combi(int &f, int &s) {
        //ALWAYS COMBINING LEFT TO RIGHT (for non-commutative operations)
        return (f+s);
    }
    int addRange(int orig, int add, int range) {
        return (orig+add*range);
    }
    int setRange(int set, int range) {
        return (set*range);
    }
    int ad(int orig, int ad) {
        //ALWAYS ADDING AD TO ORIG (for non-commutative operations)
        return (ad+orig);
    }
    SegTree(int nn): n(nn) {
        none=(inf);
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        tree.resize(2*n);
        setLazy.resize(2*n,none);
        addLazy.resize(2*n,none);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        // cout << beg << end << endl;
    }
    void prop(int i) {
        if(setLazy[i]!=none) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
    }
    void pointSet(int i, int index, int val) {
        if(i>=n) {
            tree[i]=val;
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, int val) {
        if(i>=n) {
            tree[i]=ad(tree[i], val);
            return;
        }
        prop(i);
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointAdd(2*i, index, val);
        } else {
            pointAdd(2*i+1, index, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void pointAdd(int index, int val) {
        pointAdd(1, index, val);
    }
    int rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans=combi(ans, r);
            }
        }
        return ans;
    }
    int rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, int val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            setLazy[i]=val;
            tree[i]=setRange(val, end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeSet(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeSet(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
    void rangeAdd(int left, int right, int val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, int val) {
        if(i<n) prop(i);
        if(beg[i]==left&&end[i]==right) {
            addLazy[i]=val;
            tree[i]=addRange(tree[i], val, end[i]-beg[i]+1);
            return;
        }
        if(beg[2*i]<=right&&end[2*i]>=left) {
            rangeAdd(2*i, left, min(right, end[2*i]), val);
        }
        if(beg[2*i+1]<=right&&end[2*i+1]>=left) {
            rangeAdd(2*i+1, max(left, beg[2*i+1]), right, val);
        }
        tree[i]=combi(tree[2*i], tree[2*i+1]);
    }
};
struct minSeg {
    int n;
    vt<int> beg,end;
    vt<int> mx, mn;
    //CHANGE THESE!
    int none;
    minSeg(int nn): n(nn) {
        none=inf;
        while((n&(-n))!=n) {
            n++;
        }
        beg.resize(2*n);
        end.resize(2*n);
        mx.resize(2*n);
        mn.resize(2*n);
        FOR(i, n, 2*n) {
            beg[i]=end[i]=i-n;
        }
        ROF(i, 1, n) {
            beg[i]=beg[2*i];
            end[i]=end[2*i+1];
        }
        // cout << beg << end << endl;
    }
    void pointSet(int i, int index, int val) {
        if(i>=n) {
            mx[i]=mn[i]=val;
            return;
        }
        if(beg[2*i]<=index&&end[2*i]>=index) {
            pointSet(2*i, index, val);
        } else {
            pointSet(2*i+1, index, val);
        }
        mx[i]=max(mx[2*i], mx[2*i+1]);
        mn[i]=min(mn[2*i], mn[2*i+1]);
    }
    void pointSet(int index, int val) {
        pointSet(1,index,val);
    }
    int getMin(int index, int left, int right) {
        if(beg[index]==left&&end[index]==right) return mn[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=getMin(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = getMin(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans=min(ans, r);
            }
        }
        return ans;
    }
    int getMin(int left, int right) {
        return getMin(1, left, right);
    }
    int getMax(int index, int left, int right) {
        if(beg[index]==left&&end[index]==right) return mx[index];
        int ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=getMax(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            int r = getMax(2*index+1, max(left, beg[2*index+1]), right);
            if(ans==none) {
                ans=r;
            } else {
                ans=max(ans, r);
            }
        }
        return ans;
    }
    int getMax(int left, int right) {
        return getMax(1, left, right);
    }
};
pair<int,int> solve(int n, SegTree &leftPref, SegTree &rightPref, multiset<int> &arrayVal, minSeg &mn, vt<int> &v) {
    if(leftPref.rangeQuery(0,0)==n-1) {
        return {-1,-1};
    } 
    int leftBound = leftPref.rangeQuery(0,0);
    int rightBound = rightPref.rangeQuery(n-1,n-1);
    // cout << "LINE 549 " << leftBound << " " << rightBound << endl;
    int minPoint = mn.getMin(leftBound, rightBound), maxPoint = mn.getMax(leftBound, rightBound);
    int lo = 0, hi = leftBound;
    // cout << leftBound << " " << rightBound << " " << minPoint << " " << maxPoint << endl;
    while(lo+1<hi) {
        int mid = (lo+hi)/2;
        if(v[mid]>minPoint) {
            hi=mid;
        } else {
            lo=mid;
        }
    }
    if(v[lo]<=minPoint) {
        leftBound=hi;
    } else {
        leftBound=lo;
    }
    lo=rightBound;
    hi=n-1;
    while(lo+1<hi) {
        int mid = (lo+hi)/2;
        if(v[mid]<maxPoint) {
            lo=mid;
        } else {
            hi=mid;
        }
    }
    if(v[hi]>=maxPoint) {
        rightBound = lo;
    } else {
        rightBound = hi;
    }
    return {leftBound+1, rightBound+1};
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> v(n);
        F0R(i, n) cin >> v[i];
        if(n==1) {
            int q;
            cin >> q;
            F0R(i, q) {
                int x,y;
                cin >> x >> y;
            }
            F0R(i, q+1) cout << -1 << " " << -1 << endl;
            continue;
        }
        SegTree leftPref(n);
        SegTree rightPref(n);
        int start = 0;
        FOR(i, 1, n) {
            if(v[i]<v[i-1]) {
                leftPref.rangeSet(start, i-1, i-1);
                rightPref.rangeSet(start, i-1, start);
                start=i;
            }
        }

        leftPref.rangeSet(start, n-1, n-1);
        rightPref.rangeSet(start, n-1, start);
        // F0R(i, n) {
        //     cout << i << " " << leftPref.rangeQuery(i,i).value << " " << rightPref.rangeQuery(i,i).value << endl;
        // }
        multiset<int> arrayVal;
        F0R(i, n) {
            arrayVal.insert(v[i]);
        }
        minSeg mn(n);
        F0R(i, n) {
            mn.pointSet(i, v[i]);
        }
        // cout << mn.mn << " " << mn.mx << endl;
        //HERE
        auto s = solve(n, leftPref, rightPref, arrayVal, mn, v);
        cout << s.f << " " << s.s << endl;
        int q;
        cin >> q;
        while(q--) {
            int idx, value;
            cin >> idx >> value;
            idx--;
            v[idx]=value;
            mn.pointSet(idx, value);
            // cout << mn.mn << mn.mx << endl;
            if(idx==0) {
                int end = leftPref.rangeQuery(1,1);
                int beg = 0;
                if(v[0]<=v[1]) {
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else {
                    leftPref.rangeSet(0,0,0);
                    rightPref.rangeSet(0,0,0);
                    // assert(false);
                    leftPref.rangeSet(1, end, end);
                    rightPref.rangeSet(1, end, 1);
                }
            } else if(idx==n-1) {
                int end = n-1;
                int beg = rightPref.rangeQuery(n-2,n-2);
                if(v[n-2]<=v[n-1]) {
                    // cout << "hello"
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else {
                    leftPref.rangeSet(n-1,n-1,n-1);
                    rightPref.rangeSet(n-1,n-1,n-1);
                    leftPref.rangeSet(beg, n-2, n-2);
                    rightPref.rangeSet(beg, n-2, beg);
                }
            } else {
                if(v[idx-1]<=v[idx]&&v[idx]<=v[idx+1]) {
                    int beg = rightPref.rangeQuery(idx-1,idx-1);
                    int end = leftPref.rangeQuery(idx+1, idx+1);
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else if(v[idx-1]<=v[idx]) {
                    int beg = rightPref.rangeQuery(idx-1, idx-1);
                    int end = idx;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx+1;
                    end = leftPref.rangeQuery(idx+1, idx+1);
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else if(v[idx]<=v[idx+1]) {
                    int beg = rightPref.rangeQuery(idx-1, idx-1);
                    int end = idx-1;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx;
                    end = leftPref.rangeQuery(idx+1, idx+1);
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else {
                    int beg = rightPref.rangeQuery(idx-1, idx-1);
                    int end = idx-1;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx+1;
                    end = leftPref.rangeQuery(idx+1, idx+1);
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    leftPref.rangeSet(idx, idx, idx);
                    rightPref.rangeSet(idx, idx, idx);
                }
            }
            s = solve(n, leftPref, rightPref, arrayVal, mn, v);
            cout << s.f << " " << s.s << endl;
        }
    }
    return 0;
}
/*
1
5
2 2 3 4 5
1
2 1
*/