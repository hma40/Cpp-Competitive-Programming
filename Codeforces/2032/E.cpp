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
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vt<int> a(n), ans(n);
        vt<int> oddDiff(n+2), evenDiff(n+2);
        F0R(i, n) cin >> a[i];
        if(n==1) {
            cout << 0 << endl;
            continue;
        }
        int val = a[0];
        if(n==3) {
            if(a[0]>a[1]) {
                ans[1]=a[0]-a[1];
                a[2]+=a[0]-a[1];
                a[0]+=a[0]-a[1];
                a[1]=a[0];
            } else {
                ans[0]=a[1]-a[0];
                a[2]+=a[1]-a[0];
                a[1]+=a[1]-a[0];
                a[0]=a[1];
            }
            if(a[2]>a[0]) {
                /*
                0 0 1
                1 2 2
                3 3 3
                */
                ans[1]+=a[2]-a[0];
                ans[0]+=a[2]-a[0];
            } else {
                ans[2]+=a[0]-a[2];
            }
            trav(x, ans) cout << x << " ";
            cout << endl;
            continue;
        }
        if(a[0]>a[1]) {
            ans[1]+=a[0]-a[1];
            a[2]+=a[0]-a[1];
            val=a[1]+2*(a[0]-a[1]);

        } else if(a[0]<a[1]) {
            ans[0]+=a[1]-a[0];
            a[n-1]+=a[1]-a[0];
            val=a[0]+2*(a[1]-a[0]);
        }
        // cout << "LINE 170 " << ans << a << endl;
        FOR(i, 2, n-2) {
            // cout << "LINE 173 " << i << " " << oddDiff << evenDiff << val << a << ans << endl;
            if(a[i]>val) {
                if(i%2) {
                    /*
                    0 0 0 1
                    add to 0,2 (also adds 1 to a[n-1])
                    2 2 2 2
                    */
                    evenDiff[0]+=a[i]-val;
                    evenDiff[i+1]-=a[i]-val;
                    a[n-1]+=(a[i]-val);
                    val+=2*(a[i]-val);
                    /*
                    0 0 0 2
                    4 4 4 4
                    */
                } else {
                    /*
                    0 0 0 0 1
                    add to 1,3
                    1 2 2 2 2
                    add to ans[n-1] (also adds 2 to a[n-1] and 1 to a[n-2])
                    */
                    oddDiff[1]+=a[i]-val;
                    oddDiff[i+1]-=a[i]-val;
                    ans[n-1]+=a[i]-val;
                    a[n-1]+=2*(a[i]-val);
                    a[n-2]+=a[i]-val;
                    val+=2*(a[i]-val);
                } 
            } else {
                ans[i+1]+=val-a[i];
                a[i+1]+=2*(val-a[i]);
                a[i+2]+=val-a[i];
            }

            // cout << "LINE 229 " << i << " " << oddDiff << evenDiff << val << a << ans << endl;
        }
        // cout << a[n-2] << " " << val << a << endl;
        /*
        1 2 1 2 1 3 1
        3 3 1 2 1 3 2
        3 3 3 6 3 3 2
        9 9 9 9 3 3 5
        9 9 9 9 9 15 11
        */
        /*
        1 2 1 2 20
        3 3 3 6 23
        9 9 9 9 26
        */  
        if(a[n-2]>val) {
            evenDiff[0]+=a[n-2]-val;
            evenDiff[n-1]-=a[n-2]-val;
            a[n-1]+=a[n-2]-val;
            val+=2*(a[n-2]-val);
        } else {
            // cout << "GOT TO LINE 217 " << endl;
            oddDiff[1]+=val-a[n-2];
            oddDiff[n]-=val-a[n-2];
            ans[n-1]+=(val-a[n-2]);
            a[n-1]+=(val-a[n-2])*3;
            val+=2*(val-a[n-2]);
        }
        // cout << "LINE 223lol " << oddDiff << evenDiff << val << a << ans << endl;
        for(int i = 0; i < n-1; i++) a[i]=val;
        // for(int i = 2; i < n+2; i+=2) {
        //     evenDiff[i]+=evenDiff[i-2];
        // }
        // for(int i = 3; i < n+2; i+=2) {
        //     oddDiff[i]+=oddDiff[i-2];
        // }
        // for(int i = 0; i < n; i++) {
        //     ans[i]+=oddDiff[i]+evenDiff[i];
        // }
        // cout << "LINE 233 " << oddDiff << evenDiff << val << a << ans << endl;
        /*
        1 2 1 2 20
        */

        if(a[n-1]>a[n-2]) {
            // cout << "LINE 223 " << a << endl;
            oddDiff[1]+=a[n-1]-a[n-2];
            oddDiff[n]-=a[n-1]-a[n-2];
            a[0]+=a[n-1]-a[n-2];
            a[1]+=2*(a[n-1]-a[n-2]);
            // assert(false);
            for(int i = 1; i < n; i++) a[i]=a[1];
            // cout << "LINE 230 " << a << endl;
            /*
            0 0 0 0 0 0 1
            1 2 2 2 2 2 2

            0 1 1 1 1 1 1
            remember we are adding (n-1)/2 times to first
            6 4 1 1 1 1 4
            */
            ans[0]+=n/2*(a[1]-a[0]);
            a[n-1]+=n/2*(a[1]-a[0]);
            int diff = a[1]-a[0];
            a[0]+=n/2*(diff)*2;
            a[1]+=n/2*(diff);

            // cout << a << endl;
            for(int i = 2; a[i]!=a[0]; i++) {
                // cout << i << a << endl;
                ans[i]+=a[0]-a[i-1];
                a[i]+=2*(a[0]-a[i-1]);
                a[i+1]+=a[0]-a[i-1];
                ans[n-i]+=a[0]-a[i-1];
                a[n-i]+=2*(a[0]-a[i-1]);
                a[n-i-1]+=a[0]-a[i-1];
                a[i-1]=a[0];
                a[n-i+1]=a[0];
            }
        } else {
            ans[n-1]+=n/2*(a[0]-a[n-1]);
            int diff = a[0]-a[n-1];
            a[n-1]+=n/2*2*diff;
            a[n-2]+=n/2*diff;
            a[0]+=n/2*diff;
            /*
            21 21 21 21 21 21 20
            */
            // cout << "LINE 319 " << a << endl;
            for(int i = 1; a[i]!=a[n-1]; i++) {
                ans[i]+=a[n-1]-a[i-1];
                a[i]+=2*(a[n-1]-a[i-1]);
                a[i+1]+=a[n-1]-a[i-1];
                ans[n-i-2]+=a[n-1]-a[n-i-1];
                a[n-i-2]+=2*(a[n-1]-a[n-i-1]);
                a[n-i-3]+=a[n-1]-a[n-i-1];
                a[n-i-1]=a[n-1];
                a[i-1]=n-1;
                // cout << i << a << endl;
            }
        }
        for(int i = 2; i < n+2; i+=2) {
            evenDiff[i]+=evenDiff[i-2];
        }
        for(int i = 3; i < n+2; i+=2) {
            oddDiff[i]+=oddDiff[i-2];
        }
        for(int i = 0; i < n; i++) {
            ans[i]+=oddDiff[i]+evenDiff[i];
        }
        // cout << oddDiff << evenDiff << val << a << ans << endl;
        trav(x, ans) cout << x << " ";
        cout << endl;
    }
    return 0;
}
/*
what if we have 2 numbers left?
0 0 0 0 0 1 ? (add to 0,2,4)
2 2 2 2 2 2 ?+1
0 0 0 1 0
2 2 2 2 1
0 0 0 0 0 1 0
2 2 2 2 2 2 1
2(n-2)+2

1 1 1 1 1 0 ? (add to 6,5,3,1)
3 3 3 3 3 3 ?+3
2(n-1)+3+3

1 1 1 0 ? (add to 3,1,4)
2 3 2 0 ?
2 3 3 2 ?+1
3 3 3 3 ?+3
3+2(n-1)+3

rn we have an array
we will stabilize one at a time
suppose a1,a2,...,ak already same
if ak>ak+1 then do diff array trick 
0 0 1 -> 1 2 2 -> 3 3 3
0 0 0 0 1 -> do on 2 4 ... n-1-> 1 2 2 2 2 -> 

now we only have 1 element left...suppose it is 
0 0 0 0 0 0 1
Add on 1 3 5 to turn into other case
1 1 1 1 1 1 0

0 0 0 0 1 (add 2,4)
1 2 2 2 2 

1 1 0 -> 2 2 2

1 1 1 1 0 -> 
a4+2a1+a2=3
a1+2a2+a3=3
a2+2a3+a4=3
a3+2a4+a5=3
a4+2a3+a1=4

a3=3-a1-2a2
a4=3-a2-2a3=3-a2-2(3-a1-2a2)

1 1 1 1 0
2 1 1 2 2
2 2 3 3 2
3 4 4 3 2
4 4 4 4 4

1 1 1 1 0
3 1 1 3 4
4 4 4 4 4

1 1 0 (3)
2 2 2

1 1 1 1 0 (5)
2 1 1 2 2 (3)
2 2 3 3 2 (2)
3 4 4 3 2 (5)
4 4 4 4 4 

1 1 1 1 1 1 0 (7 x3)
4 1 1 1 1 4 6 (5 x2)
4 1 1 3 5 6 6 (4 x1)
4 1 2 5 6 6 6 (3 x1)
4 2 4 6 6 6 6 (2 x2)
6 6 6 6 6 6 6

1 1 1 1 1 1 1 1 0 (9 x4)
5 1 1 1 1 1 1 5 8 (7 x3)
5 1 1 1 1 4 7 8 8 (2 x3)
8 7 4 1 1 4 7 8 8 (3 x1, 6 x1)
8 8 5 2 2 5 8 8 8 (4 x2, 5 x2)
8 8 8 8 8 8 8 8 8


*/