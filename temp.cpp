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
struct Node {
    int value;
    Node(int val): value(val){

    };
    Node() {
        value=0;
    }
};
struct SegTree {
    int n;
    vt<int> beg,end;
    vt<Node> tree;
    vt<Node> setLazy;
    vt<Node> addLazy; 
    //CHANGE THESE!
    Node none;
    Node combi(Node &f, Node &s) {
        //ALWAYS COMBINING LEFT TO RIGHT (for non-commutative operations)
        return Node(f.value+s.value);
    }
    Node addRange(Node orig, Node add, int range) {
        return Node(orig.value+add.value*range);
    }
    Node setRange(Node set, int range) {
        return Node(set.value*range);
    }
    Node ad(Node orig, Node ad) {
        //ALWAYS ADDING AD TO ORIG (for non-commutative operations)
        return Node(ad.value+orig.value);
    }
    SegTree(int nn): n(nn) {
        none=Node(inf);
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
        if(setLazy[i].value!=none.value) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i].value!=none.value) {
            if(setLazy[2*i].value!=none.value) {
                setLazy[2*i]=ad(setLazy[2*i], addLazy[i]);
            } else if(addLazy[2*i].value!=none.value) {
                addLazy[2*i]=ad(addLazy[2*i], addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1].value!=none.value) {
                setLazy[2*i+1]=ad(setLazy[2*i+1], addLazy[i]);
            } else if(addLazy[2*i+1].value!=none.value) {
                addLazy[2*i+1]=ad(addLazy[2*i+1], addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]=addRange(tree[2*i+1], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            tree[2*i]=addRange(tree[2*i], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, Node val) {
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
    void pointSet(int index, Node val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, Node val) {
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
    void pointAdd(int index, Node val) {
        pointAdd(1, index, val);
    }
    Node rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        Node ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            Node r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans.value==none.value) {
                ans=r;
            } else {
                ans=combi(ans, r);
            }
        }
        return ans;
    }
    Node rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, Node val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, Node val) {
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
    void rangeAdd(int left, int right, Node val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, Node val) {
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
    vt<Node> tree;
    vt<Node> setLazy;
    vt<Node> addLazy; 
    //CHANGE THESE!
    Node none;
    Node combi(Node &f, Node &s) {
        //ALWAYS COMBINING LEFT TO RIGHT (for non-commutative operations)
        return Node(min(f.value,s.value));
    }
    Node addRange(Node orig, Node add, int range) {
        return Node(orig.value+add.value*range);
    }
    Node setRange(Node set, int range) {
        return Node(set.value*range);
    }
    Node ad(Node orig, Node ad) {
        //ALWAYS ADDING AD TO ORIG (for non-commutative operations)
        return Node(ad.value+orig.value);
    }
    minSeg(int nn): n(nn) {
        none=Node(inf);
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
        if(setLazy[i].value!=none.value) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i].value!=none.value) {
            if(setLazy[2*i].value!=none.value) {
                setLazy[2*i]=ad(setLazy[2*i], addLazy[i]);
            } else if(addLazy[2*i].value!=none.value) {
                addLazy[2*i]=ad(addLazy[2*i], addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1].value!=none.value) {
                setLazy[2*i+1]=ad(setLazy[2*i+1], addLazy[i]);
            } else if(addLazy[2*i+1].value!=none.value) {
                addLazy[2*i+1]=ad(addLazy[2*i+1], addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]=addRange(tree[2*i+1], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            tree[2*i]=addRange(tree[2*i], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, Node val) {
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
    void pointSet(int index, Node val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, Node val) {
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
    void pointAdd(int index, Node val) {
        pointAdd(1, index, val);
    }
    Node rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        Node ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            Node r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans.value==none.value) {
                ans=r;
            } else {
                ans=combi(ans, r);
            }
        }
        return ans;
    }
    Node rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, Node val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, Node val) {
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
    void rangeAdd(int left, int right, Node val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, Node val) {
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
struct maxSeg {
    int n;
    vt<int> beg,end;
    vt<Node> tree;
    vt<Node> setLazy;
    vt<Node> addLazy; 
    //CHANGE THESE!
    Node none;
    Node combi(Node &f, Node &s) {
        //ALWAYS COMBINING LEFT TO RIGHT (for non-commutative operations)
        return Node(max(f.value, s.value));
    }
    Node addRange(Node orig, Node add, int range) {
        return Node(orig.value+add.value*range);
    }
    Node setRange(Node set, int range) {
        return Node(set.value*range);
    }
    Node ad(Node orig, Node ad) {
        //ALWAYS ADDING AD TO ORIG (for non-commutative operations)
        return Node(ad.value+orig.value);
    }
    maxSeg(int nn): n(nn) {
        none=Node(inf);
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
        if(setLazy[i].value!=none.value) {
            setLazy[2*i]=setLazy[i];
            setLazy[2*i+1]=setLazy[i];
            tree[2*i]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            tree[2*i+1]=setRange(setLazy[i], end[2*i]-beg[2*i]+1);
            addLazy[2*i]=none;
            addLazy[2*i+1]=none;
            setLazy[i]=none;
        }   
        if(addLazy[i].value!=none.value) {
            if(setLazy[2*i].value!=none.value) {
                setLazy[2*i]=ad(setLazy[2*i], addLazy[i]);
            } else if(addLazy[2*i].value!=none.value) {
                addLazy[2*i]=ad(addLazy[2*i], addLazy[i]);
            } else {
                addLazy[2*i]=addLazy[i];
            }
            if(setLazy[2*i+1].value!=none.value) {
                setLazy[2*i+1]=ad(setLazy[2*i+1], addLazy[i]);
            } else if(addLazy[2*i+1].value!=none.value) {
                addLazy[2*i+1]=ad(addLazy[2*i+1], addLazy[i]);
            } else {
                addLazy[2*i+1]=addLazy[i];
            }
            tree[2*i+1]=addRange(tree[2*i+1], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            tree[2*i]=addRange(tree[2*i], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
            addLazy[i]=none;
        }
    }
    void pointSet(int i, int index, Node val) {
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
    void pointSet(int index, Node val) {
        pointSet(1,index,val);
    }
    void pointAdd(int i, int index, Node val) {
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
    void pointAdd(int index, Node val) {
        pointAdd(1, index, val);
    }
    Node rangeQuery(int index, int left, int right) {
        if(index<n) prop(index);
        if(beg[index]==left&&end[index]==right) return tree[index];
        Node ans = none;
        if(beg[2*index]<=right&&end[2*index]>=left) {
            ans=rangeQuery(2*index, left, min(right, end[2*index]));
        }
        if(beg[2*index+1]<=right&&end[2*index+1]>=left) {
            Node r = rangeQuery(2*index+1, max(left, beg[2*index+1]), right);
            if(ans.value==none.value) {
                ans=r;
            } else {
                ans=combi(ans, r);
            }
        }
        return ans;
    }
    Node rangeQuery(int left, int right) {
        return rangeQuery(1, left, right);
    }
    void rangeSet(int left, int right, Node val) {
        rangeSet(1,left,right,val);
    }
    void rangeSet(int i, int left, int right, Node val) {
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
    void rangeAdd(int left, int right, Node val) {
        rangeAdd(1, left, right, val);
    }
    void rangeAdd(int i, int left, int right, Node val) {
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
struct fake {
    pair<int,int> solve(int n, SegTree &leftPref, SegTree &rightPref, multiset<int> &arrayVal, minSeg &mn, maxSeg &mx, vt<int> &v) {
        if(leftPref.rangeQuery(0,0).value==n-1) {
            return {-1,-1};
        } 
        int leftBound = leftPref.rangeQuery(0,0).value;
        int rightBound = rightPref.rangeQuery(n-1,n-1).value;
        int minPoint = mn.rangeQuery(leftBound, rightBound).value, maxPoint = mx.rangeQuery(leftBound, rightBound).value;
        int lo = 0, hi = leftBound;
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

    string hello(int n, vt<int> v, int q, vt<pair<int,int>> queries) {
        string ans = "";
        if(n==1) {
            F0R(i, q+1) ans+="-1 -1\n";
            return ans;
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
        multiset<int> arrayVal;
        F0R(i, n) {
            arrayVal.insert(v[i]);
        }
        minSeg mn(n);
        maxSeg mx(n);
        F0R(i, n) {
            mn.pointSet(i, v[i]);
            mx.pointSet(i, v[i]);
        }
        //HERE
        auto s = solve(n, leftPref, rightPref, arrayVal, mn, mx, v);
        ans+=to_string(s.f)+" " +to_string(s.s)+"\n";
        F0R(qq, q) {
            int idx, value;
            idx = queries[qq].f;
            value = queries[qq].s;
            idx--;
            v[idx]=value;
            mn.pointSet(idx, value);
            mx.pointSet(idx, value);
            if(idx==0) {
                int end = leftPref.rangeQuery(1,1).value;
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
                int beg = rightPref.rangeQuery(n-2,n-2).value;
                if(v[n-2]<=v[n-1]) {
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
                    int beg = rightPref.rangeQuery(idx-1,idx-1).value;
                    int end = leftPref.rangeQuery(idx+1, idx+1).value;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else if(v[idx-1]<=v[idx]) {
                    int beg = rightPref.rangeQuery(idx-1, idx-1).value;
                    int end = idx;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx+1;
                    end = leftPref.rangeQuery(idx+1, idx+1).value;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else if(v[idx]<=v[idx+1]) {
                    int beg = rightPref.rangeQuery(idx-1, idx-1).value;
                    int end = idx-1;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx;
                    end = leftPref.rangeQuery(idx+1, idx+1).value;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                } else {
                    int beg = rightPref.rangeQuery(idx-1, idx-1).value;
                    int end = idx-1;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    beg = idx+1;
                    end = leftPref.rangeQuery(idx+1, idx+1).value;
                    leftPref.rangeSet(beg, end, end);
                    rightPref.rangeSet(beg, end, beg);
                    leftPref.rangeSet(idx, idx, idx);
                    rightPref.rangeSet(idx, idx, idx);
                }
            }
            s = solve(n, leftPref, rightPref, arrayVal, mn, mx, v);
            ans+=to_string(s.f)+" " +to_string(s.s)+"\n";
        }
        return ans;
    }
};
struct reall {
    pair<int,int> solve(vt<int> v) {
        vt<int> temp = v;
        vt<int> sorted = v;
        sort(begin(sorted),end(sorted));
        sort(begin(temp),end(temp));
        if(temp==v) return {-1,-1};
        int n = v.size();
        FOR(size, 1, n) {
            F0R(start, n-size) {
                temp = v;
                sort(begin(temp)+start, begin(temp)+start+size+1);
                // cout << v << " " << start << " " << start+size << " " << temp << endl;
                if(temp==sorted) {
                    return {start+1, start+size+1};
                }
            }
        }
    }
    string hello(int n, vt<int> v, int q, vt<pair<int,int>> queries) {  
        string ans = "";
        auto s = solve(v);
        ans+=to_string(s.f) +" " +to_string(s.s)+"\n";
        F0R(i, q) {
            v[queries[i].f-1]=queries[i].s;
            auto s = solve(v);
            ans+=to_string(s.f) +" " +to_string(s.s)+"\n";
        }
        return ans;
    }
};
signed main() {
    while(true) {
        int n = 5;
        int q = 2;
        vt<int> v(n);
        F0R(i, n) {
            v[i]=rand()%10-5;
        }
        vt<pair<int,int>> queries(q);
        F0R(i, q) {
            queries[i].f=rand()%n+1;
            queries[i].s=rand()%10-5;
        }
        reall r;
        fake f;
        string re = r.hello(n, v, q, queries);
        string fa = f.hello(n, v, q, queries);
        if(re==fa) {
            cout << "PASSED" << endl;
        } else {
            cout << "WRONG ANSWER PRETEST 2" << endl;
            cout << v << queries << endl;
            cout << re << endl;
            cout << fa << endl;
            break;
        }
    }
}