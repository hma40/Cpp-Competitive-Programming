#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
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

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop_front();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
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
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
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
#define double long double
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef unsigned long long ull;
typedef __uint128_t L;
ll mod = 1000000007;
struct FastMod {
	ull b, m;
	FastMod(ull bb) : b(bb), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b; // can be proven that 0 <= r < 2*b
		return r >= b ? r - b : r;
	}
};
FastMod fs(mod);
struct Node {
    Node* prev;
    Node* next;
    int value; 
    bool good; //true if and only if its next has value 1 greater than current Node's value
    Node(int val) {
        this->value=val;
        this->prev=nullptr;
        this->next=nullptr;
        good=false;
    }
};
std::ostream& operator<<(std::ostream& os, Node* n) {
    if(n->next==nullptr) {
        cout << "{" << n->value << ", " << n->good << "}";
        return os;
    }
    cout << "{" << n->value << ", " << n->good << "}" << "->" << n->next;
    return os;
}
struct SqrtLinkedList {
    int sz = 451;
    vector<Node*> beginRef;
    int nodes = 1, goodNodes = 1;
    SqrtLinkedList(int initial) {
        Node* n = new Node(initial);
        n->good=true;
        beginRef.push_back(n);
    }
    Node* get(int ind) {
        int flr = ind/sz;
        int num = flr*sz;
        Node* cur = beginRef[flr];
        while(num<ind) {
            num++;
            cur=cur->next;
        }
        return cur;
    }
    void del(int ind) {

        if(nodes==1) {
            goodNodes=0;
            nodes=0;
            beginRef.clear();
            return;
        }
        Node* cur = get(ind);   
        nodes--;
        // cout << "LINE 190 " << cur << endl;
        if(cur->good) {
            goodNodes--;
        }
        //special case: ind==0
        if(ind==0) {
            cur->next->prev=nullptr;
            for (int i = 0; i < beginRef.size() - 1; i++) {
                beginRef[i] = beginRef[i]->next;
            }
            Node* last = beginRef.back();
            if (last->next != nullptr) {
                beginRef.back() = last->next;
            } else {
                beginRef.pop_back();
            }
            return;
        }
        // cout << "LINE 207 " << cur << endl;
        //special case: ind is last node
        Node* prev = cur->prev;
        if(ind==nodes) {
            //index offset by 1 because we already decreased nodes
            if(ind%sz==0) {
                beginRef.pop_back(); //if beginRef is referencing last node then we delete it
            }
            if(!prev->good) {
                prev->good=true;
                goodNodes++;
            }
            prev->next=nullptr;
            return;
        }

        Node* aft = cur->next;
        // cout << "LINE 220 " << prev << " " << aft << endl;
        // cout << prev->good << " " << prev->value << " " << aft->value << endl;
        if(aft->value==prev->value+1) {//only node whose good can change is prev
            prev->good=true;
            goodNodes++;
        }
        prev->next=aft;
        aft->prev=prev;
        if(prev->good&&prev->value+1!=aft->value) {
            prev->good=false;
            goodNodes--;
        }
        int flr = (ind+sz-1)/sz;
        for (int i = flr; i < beginRef.size() - 1; i++) {
            beginRef[i] = beginRef[i]->next;
        }
        if(flr<=beginRef.size()-1) {
            Node* last = beginRef.back();
            if (last->next != nullptr) {
                beginRef.back() = last->next;
            } else {
                beginRef.pop_back();
            }
        }
    }
    void insert(int ind, int element) {
        //special case: ind=0
        if(nodes==0) {
            nodes=1;
            goodNodes=1;
            Node* n = new Node(element);
            n->good=true;
            beginRef.push_back(n);
            return;
        }
        Node* n = new Node(element);
        nodes++;
        if(ind==0) {
            Node* fir = get(0);
            n->next=fir;
            fir->prev=n;
            if(n->value+1==fir->value) {
                goodNodes++;
                n->good=true;
            }
            for(int i = 0; i < beginRef.size(); i++) {
                beginRef[i]=beginRef[i]->prev;
            }
            if(nodes%sz==1) {
                Node* lst = get(nodes-2);
                beginRef.push_back(lst->next);
            }
            return;
        }
        Node* prev = get(ind-1);
        if(ind==nodes-1) {
            n->good=true;
            goodNodes++;
            if(prev->value+1!=element) {
                prev->good=false;
                goodNodes--;
            }
            prev->next=n;
            n->prev=prev;
            if(nodes%sz==1) {
                beginRef.push_back(n);
            }
            return;
        }
        Node* aft = get(ind);
        if(aft->value==n->value+1) {
            n->good=true;
            goodNodes++;
        }
        if(prev->value+1==aft->value) {
            prev->good=false;
            goodNodes--;
        }
        if(prev->value+1==n->value) {
            prev->good=true;
            goodNodes++;
        }
        prev->next=n;
        aft->prev=n;
        n->prev=prev;
        n->next=aft;
        int flr = (ind+sz-1)/sz;
        for(int i = flr; i < beginRef.size(); i++) {
            beginRef[i]=beginRef[i]->prev;
        }
        if(nodes%sz==1) {
            auto last = get(nodes-2);
            beginRef.push_back(last->next);
        }
    }
};
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
std::ostream& operator<<(std::ostream& os, SqrtLinkedList n) {
    // cout << n.beginRef[0] << endl;
    cout << n.beginRef;
    return os;
}
struct SegTree {
    int n;
    vt<int> tree;
    SegTree(int nn) {
        int np = 1;
        while(np<nn) np*=2;
        tree.resize(2*np);
        n=np;
    }
    void build(vt<int> &arr) {
        for(int i = 0; i < arr.size(); i++) {
            tree[i+n]=arr[i];
        }
        for(int i = n-1; i > 0; i--) {
            //CHANGE HERE
            tree[i]=tree[2*i]+tree[2*i+1];
        }
    }
    void set(int pos, int x) {
        pos+=n;
        tree[pos]=x;
        for(pos/=2; pos; pos/=2) {
            //CHANGE HERE
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    void add(int pos, int x) {
        pos+=n;
        tree[pos]+=x;
        for(pos/=2; pos; pos/=2) {
            tree[pos]=tree[2*pos]+tree[2*pos+1];
        }
    }
    int rangeQuery(int a, int b) {
        if(a>b) return 0;
        a+=n;
        int ans = 0;
        b+=n;
        while(a<=b) {
            if(a%2==1) ans+=tree[a++];
            if(b%2==0) ans+=tree[b--];
            a/=2;
            b/=2;
        }
        return ans;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int tt;
    cin >> tt;
    while(tt--) {
        int n,m,q;
        cin >> n >> m >> q;
        vt<int> inv(n);
        F0R(i, n) {
            int x;
            cin >> x;
            x--;
            inv[x]=i;
        }
        vt<set<int>> active(n);
        vt<int> b(m);
        F0R(i, m) {
            cin >> b[i];
            b[i]--;
            b[i]=inv[b[i]];
            active[b[i]].insert(i);
        }
        // cout << b << endl;
        SegTree st(m);
        F0R(i, n) {
            if(active[i].size()==0) continue;
            st.add(*(active[i].begin()), 1);
        }
        SqrtLinkedList sqr(b[0]);
        FOR(i, 1, m) {
            if((*active[b[i]].begin())==i) {
                sqr.insert(sqr.nodes, b[i]);
            }
        }
        // cout << sqr << endl;
        // cout << active << endl;
        if(sqr.goodNodes==sqr.nodes&&b[0]==0) {
            cout << "YA" << endl;
        } else {
            cout << "TIDAK" << endl;
        }
        F0R(i, q) {
            int s,t;
            cin >> s >> t;
            s--;
            t--;
            // cout << s << " " << t << inv << " " << inv[t] << active << endl;
            t=inv[t];
            // cout << "LINE 428 " << t << endl;
            auto firstS = *active[b[s]].begin();
            active[b[s]].erase(s);
            // assert(false);
            // cout << b[s] << " " << active[b[s]] << " " << firstS << endl;
            if(firstS==s) {
                // cout << "LINE 434 " << endl;
                int del = st.rangeQuery(0, s-1);
                // cout << "LINE 436 " << del << sqr << endl;
                sqr.del(del);
                // cout << "LINE 424 " << sqr << sqr.nodes << " " << sqr.goodNodes << endl;
                st.set(s, 0);
                if(active[b[s]].size()) {
                    firstS = *active[b[s]].begin();
                    del=st.rangeQuery(0, firstS-1);
                    st.set(firstS, 1);
                    sqr.insert(del, b[s]);
                }
            }
            // cout << "GOT TO LINE 443 " << endl;
            // cout << "LINE 45252 " << sqr << sqr.nodes << " " << sqr.goodNodes << endl;
            // cout << st.tree << endl;
            b[s]=t;
            // cout << "LINE 447 " << t << " " << b[s] << endl;
            if(active[b[s]].size()) {
                int beg = *active[b[s]].begin();
                if(beg>s) {
                    // cout << "GOT TO LINE 449 " << endl;
                    int del = st.rangeQuery(0, beg-1);
                    sqr.del(del);
                    // cout << "LINE 46161 " << sqr << sqr.nodes << " " << sqr.goodNodes << endl;
                    st.set(beg, 0);
                    st.set(s, 1);
                    del = st.rangeQuery(0, s-1);
                    sqr.insert(del, b[s]);
                    // cout << "GOT TO LINE 457 " << endl;
                }
            } else {
                st.set(s, 1);
                int del = st.rangeQuery(0, s-1);
                sqr.insert(del, b[s]);
            }
            // cout << "GOT TO LINE 463 " << endl;
            // cout << b[s] << " " << t << endl;
            // cout << active << endl;
            // cout << "LINE 466 "  << active[b[s]] << endl;
            active[b[s]].insert(s);
            if(sqr.nodes==sqr.goodNodes&&b[0]==0) {
                cout << "YA" << endl;
            } else {
                cout << "TIDAK" << endl;
            }
            // cout << "LINE 477 " << sqr << sqr.nodes << " " << sqr.goodNodes << b << endl;
            // cout << st.tree << endl;
        }
    }
    return 0;
}
/*
1
6 2 3
5 1 4 3 2 6
5 6
1 6
1 5
2 2

*/