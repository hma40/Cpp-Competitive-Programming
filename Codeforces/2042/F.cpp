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
        q.pop();
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

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
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
// #define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
int MAX_N=262144;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
vt<vt<int>> ind2(5, vt<int>(5, -1));
vt<int> a(MAX_N), b(MAX_N);
struct SegTree {
    int n = MAX_N;
    vector<array<int,15>> tree;
    vt<int> left, right;
    SegTree() {
        tree.resize(2*n);
        FOR(i, 1, 2*n) tree[i].fill(-inf);
        left.resize(2*n);
        right.resize(2*n);
        F0R(i, n) {
            left[i+n]=i;
            right[i+n]=i;
        }
        ROF(i, 1, n) {
            left[i]=left[i*2];
            right[i]=right[i*2+1];
        }
        F0R(i, n) {
            tree[i+n][ind2[0][0]]=0;
            tree[i+n][ind2[0][1]]=a[i]+b[i];
            tree[i+n][ind2[0][2]]=a[i]+2*b[i];
            tree[i+n][ind2[1][1]]=a[i];
            tree[i+n][ind2[1][2]]=a[i]+b[i];
            tree[i+n][ind2[2][2]]=0;
            tree[i+n][ind2[2][3]]=a[i]+b[i];
            tree[i+n][ind2[2][4]]=a[i]+2*b[i];
            tree[i+n][ind2[3][3]]=a[i];
            tree[i+n][ind2[3][4]]=a[i]+b[i];
            tree[i+n][ind2[4][4]]=0;
        }
        ROF(i, 1, n) {
            F0R(startState, 5) {
                FOR(endState, startState, 5) {
                    FOR(midState, startState, endState+1) {
                        tree[i][ind2[startState][endState]]=max(tree[i][ind2[startState][endState]], tree[2*i][ind2[startState][midState]]+tree[2*i+1][ind2[midState][endState]]);
                    }
                }
            }
        }
    }
    void update(int i, int idx) {
        // cout << "UPDATE CALLED " << i << " " << idx << endl;
        if(left[i]==idx&&right[i]==idx) {
            tree[i][ind2[0][0]]=0;
            tree[i][ind2[0][1]]=a[idx]+b[idx];
            tree[i][ind2[0][2]]=a[idx]+2*b[idx];
            tree[i][ind2[1][1]]=a[idx];
            tree[i][ind2[1][2]]=a[idx]+b[idx];
            tree[i][ind2[2][2]]=0;
            tree[i][ind2[2][3]]=a[idx]+b[idx];
            tree[i][ind2[2][4]]=a[idx]+2*b[idx];
            tree[i][ind2[3][3]]=a[idx];
            tree[i][ind2[3][4]]=a[idx]+b[idx];
            tree[i][ind2[4][4]]=0;
            // cout << tree[i] << endl;
            return;
        } 
        if(left[2*i]<=idx&&right[2*i]>=idx) {
            update(2*i, idx);
        } else {
            update(2*i+1, idx);
        }
        tree[i].fill(-inf);
        F0R(startState, 5) {
            FOR(endState, startState, 5) {
                FOR(midState, startState, endState+1) {
                    tree[i][ind2[startState][endState]]=max(tree[i][ind2[startState][endState]], tree[2*i][ind2[startState][midState]]+tree[2*i+1][ind2[midState][endState]]);
                }
            }
        }
        // cout << tree[i] << endl;
    }
    array<int,15> query(int i, int l, int r) {
        // cout << "QUERY CALLED FOR " << i << " " << l << " " << r << endl;
        if(l==left[i]&&r==right[i]) {
            // cout << "RETURNING " << tree[i] << endl;
            return tree[i];
        }
        
        if(left[2*i]<=r&&right[2*i]>=l) {
            array<int,15> ans=query(2*i, l, min(right[2*i], r));
            if(left[2*i+1]<=r&&right[2*i+1]>=l) {
                array<int,15> temp = query(2*i+1, max(l, left[2*i+1]), r);
                array<int,15> temp2;
                temp2.fill(-inf);
                F0R(startState, 5) {
                    FOR(endState, startState, 5) {
                        FOR(midState, startState, endState+1) {
                            temp2[ind2[startState][endState]]=max(temp2[ind2[startState][endState]], ans[ind2[startState][midState]]+temp[ind2[midState][endState]]);
                        }
                    }
                }
                // cout << "RETURNING " << temp2 << endl;
                return temp2;
            }
            // cout << "RETURNING " << ans << endl;
            return ans;
        }
        return query(2*i+1, max(l, left[2*i+1]), r);
        // auto temp = query(2*i+1, max(l, left[2*i+1]), r);
        // cout << "RETURNING " << temp << endl;
        // return temp;
    }
};
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int nxt = 0;
    F0R(i, 5) {
        FOR(j, i, 5) {
            ind2[i][j]=nxt++; 
        }
    }
    // return 0;
    int n;
    cin >> n;
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    SegTree st;
    // F0R(i, 2*MAX_N) {
    //     cout << i << " " << st.tree[i] << endl;
    // }
    // cout << st.left << endl << st.right << endl;
    int q;
    cin >> q;
    while(q--) {
        int x,l,r;
        cin >> x >> l >> r;
        if(x==1) {
            a[l-1]=r;
            st.update(1, l-1);
        } else if(x==2) {
            b[l-1]=r;
            st.update(1, l-1);
        } else {
            cout << st.query(1, l-1, r-1)[ind2[0][4]] << endl;
            // F0R(i, 2*n) cout << i << " " << st.tree[i] << endl;
        }
    }
}
