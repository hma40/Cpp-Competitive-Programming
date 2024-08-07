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
            return max(f,s);
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
            if(addLazy[i]!=none) {
                if(setLazy[2*i]!=none) {
                    setLazy[2*i]=ad(setLazy[2*i], addLazy[i]);
                } else if(addLazy[2*i]!=none) {
                    addLazy[2*i]=ad(addLazy[2*i], addLazy[i]);
                } else {
                    addLazy[2*i]=addLazy[i];
                }
                if(setLazy[2*i+1]!=none) {
                    setLazy[2*i+1]=ad(setLazy[2*i+1], addLazy[i]);
                } else if(addLazy[2*i+1]!=none) {
                    addLazy[2*i+1]=ad(addLazy[2*i+1], addLazy[i]);
                } else {
                    addLazy[2*i+1]=addLazy[i];
                }
                tree[2*i+1]=addRange(tree[2*i+1], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
                tree[2*i]=addRange(tree[2*i], addLazy[i], end[2*i+1]-beg[2*i+1]+1);
                addLazy[i]=none;
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
    signed main() {
        ios_base::sync_with_stdio(false); 
        cin.tie(0);
        int t;
        cin >> t;
        while(t--) {
            int n;
            cin >> n;
            vt<int> a(n);
            F0R(i, n) cin >> a[i];
            SegTree st(2*n+5);
            int sum = 0;
            FOR(i, 0, 2*n) {
                sum+=a[i%n];
                st.pointSet(i+1, sum);
            }
            if(sum>0) {
                F0R(i, n) cout << n << " ";
                cout << endl;
                continue;
            }
            // cout << st.tree << endl;
            F0R(i, n) {
                int end = i+n;
                if(st.rangeQuery(i, end)-st.rangeQuery(i,i)<=0) {
                    cout << -1 << " ";
                } else {
                    int beg = i, ed= i+n;
                    while(beg+1<ed) {
                        int mid = (beg+ed)/2;
                        // cout << beg << " " << ed << " " << mid << endl;
                        // cout << beg << " " << mid << " " << ed << endl;
                        if(st.rangeQuery(mid, end)-st.rangeQuery(i,i)<=0) {
                            ed=mid;
                        } else {
                            beg=mid;
                        }
                    }
                    if(st.rangeQuery(ed,end)-st.rangeQuery(i,i)<=0) {
                        // cout << "GOT TO LINE 248 " << ed << " " << i << endl;
                        cout << (ed-1-i) << " ";
                    } else {
                        // cout << "GOT TO LINE 251 " << beg << " " << i << endl;
                        cout << (beg-1-i) << " ";
                    }
                }

            }  
            cout << endl;
        }
        return 0;
    }
    /*
    1
    3
    -4 2 7
    */