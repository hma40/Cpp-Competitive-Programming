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
vt<int> perm;
vt<vt<int>> children;
vt<int> par;
int n,q;
vt<int> subSize;
vt<int> invPerm;
vt<set<int>> wrongLoc;
// vt<multiset<int>> extras,missing;
set<int> problems;//a node is in problems if and only if its children are in the wrong spots OR it is not in its expected location
vt<int> expectedLocation;
vt<set<pair<int,int>>> actualChildrenLoc;
void dfs(int node=0) {
    trav(x, children[node]) {
        dfs(x);
        // missing[node].insert(subSize[x]);
        subSize[node]+=subSize[x];
    }
}
void reset() {
    wrongLoc.assign(n, set<int>());
    invPerm.assign(n,0);
    perm.assign(n,0);
    children.assign(n,vt<int>());
    par.assign(n,-1);
    subSize.assign(n,1);
    actualChildrenLoc.assign(n, set<pair<int,int>>());
    // extras.assign(n, multiset<int>());
    // missing.assign(n, multiset<int>());
    problems.clear();
    expectedLocation.assign(n, -50);
    F0R(i, n) {
        actualChildrenLoc[i].insert({inf,inf});
        actualChildrenLoc[i].insert({-inf, -inf});
    }
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int t = 1;
    cin >> t;
    while(t--) {
        cin >> n >> q;
        reset();
        FOR(i, 1, n) {
            cin >> par[i];
            par[i]--;
            children[par[i]].add(i);
        }
        F0R(i, n) {
            cin >> perm[i];
            perm[i]--;
        }
        // assert(false);
        dfs();
        F0R(i, n) invPerm[perm[i]]=i;
        // assert(false);
        F0R(i, n) {
            trav(x, children[i]) {
                // cout << i << " " << x << endl;
                actualChildrenLoc[i].insert({invPerm[x], x});
            }
        }
        R0F(i, n) {
            if(children[i].size()==0) {
                continue;
            }
            // bool good = true;
            trav(x, children[i]) {
                auto next = *(actualChildrenLoc[i].upper_bound({invPerm[x], x}));
                if(next.f==inf) continue;
                if(next.f-invPerm[x]!=subSize[x]) {
                    // good=false;
                    wrongLoc[i].insert(x);
                }
            }
            if(wrongLoc[i].size()==0) {
                auto firstReal = actualChildrenLoc[i].begin();
                firstReal++;
                expectedLocation[i]=(*firstReal).f-1;
                if(invPerm[i]!=expectedLocation[i]) {
                    problems.insert(i);
                }
            } else {
                problems.insert(i);
            }
        }
        // cout << problems << expectedLocation << wrongLoc << endl;
        F0R(i, q) {
            int x,y;
            cin >> x >> y;
            x--;
            y--;
            //check if x and y messed up their parents  
            int pr = par[perm[x]];
            if(perm[x]!=0) {
                // int pr = par[x];

                wrongLoc[pr].erase(perm[x]);
                auto after = actualChildrenLoc[pr].find({x, perm[x]});
                after++;
                auto bef = actualChildrenLoc[pr].find({x,perm[x]});
                bef--;
                if((*after).f==inf) {
                    //bef is good
                    wrongLoc[pr].erase((*bef).s);
                } else if((*bef).f!=-inf) {
                    //check if bef is fine
                    if((*after).f-(*bef).f==subSize[(*bef).s]) {
                        wrongLoc[pr].erase((*bef).s);
                    } else {
                        wrongLoc[pr].insert((*bef).s);
                    }
                }         
                actualChildrenLoc[pr].erase({x, perm[x]});
            }
            // assert(false);

            // assert(false);
            pr=par[perm[y]];
            if(perm[y]!=0) {
                // int pr = par[x];
                wrongLoc[pr].erase(perm[y]);
                auto after = actualChildrenLoc[pr].find({y, perm[y]});
                after++;
                auto bef = actualChildrenLoc[pr].find({y,perm[y]});
                bef--;
                // cout << actualChildrenLoc[pr] << (*after) << (*bef) << endl;
                if((*after).f==inf) {
                    //bef is good
                    wrongLoc[pr].erase((*bef).s);
                } else if((*bef).f!=-inf) {
                    //check if bef is fine
                    if((*after).f-(*bef).f==subSize[(*bef).s]) {
                        wrongLoc[pr].erase((*bef).s);
                    } else {
                        wrongLoc[pr].insert((*bef).s);
                    }
                }     
                actualChildrenLoc[pr].erase({y, perm[y]});
            }
            // assert(false);

            swap(perm[x], perm[y]);
            invPerm[perm[x]]=x;
            invPerm[perm[y]]=y;
            // assert(false);
            if(perm[x]!=0) {
                pr=par[perm[x]];
                actualChildrenLoc[pr].insert({x, perm[x]});
                auto after = actualChildrenLoc[pr].find({x, perm[x]});
                after++;
                auto bef = actualChildrenLoc[pr].find({x,perm[x]});
                bef--;
                // cout << "LINE 291 " << actualChildrenLoc[pr] << (*after) << (*bef) << endl;
                if((*after).f==inf) {
                    //x is fine
                    wrongLoc[pr].erase(perm[x]);
                } else {
                    if((*after).f-x==subSize[perm[x]]) {
                        wrongLoc[pr].erase(perm[x]);
                    } else {
                        wrongLoc[pr].insert(perm[x]);
                    }
                } 
                // cout << "LINE 302 " << subSize[(*bef).s] << endl;
                if((*bef).f!=-inf) {
                    if(x-(*bef).f==subSize[(*bef).s]) {
                        wrongLoc[pr].erase((*bef).s);
                    } else {
                        wrongLoc[pr].insert((*bef).s);
                    }
                }
                if(wrongLoc[pr].size()) {
                    expectedLocation[pr]=-50;
                    problems.insert(pr);
                } else {
                    auto firstReal = actualChildrenLoc[pr].begin();
                    firstReal++;
                    expectedLocation[pr]=(*firstReal).f-1;
                    // cout << "LINE 317 " << pr << " " << invPerm[pr] << " " << expectedLocation[pr] << endl;
                    if(invPerm[pr]!=expectedLocation[pr]) {
                        problems.insert(pr);
                    } else {
                        problems.erase(pr);
                    }
                }
            }
            // assert(false);
            if(perm[y]!=0) {
                pr=par[perm[y]];
                actualChildrenLoc[pr].insert({y, perm[y]});
                auto after = actualChildrenLoc[pr].find({y, perm[y]});
                after++;
                auto bef = actualChildrenLoc[pr].find({y,perm[y]});
                bef--;
                if((*after).f==inf) {
                    //x is fine
                    wrongLoc[pr].erase(perm[y]);
                } else {
                    if((*after).f-y==subSize[perm[y]]) {
                        wrongLoc[pr].erase(perm[y]);
                    } else {
                        wrongLoc[pr].insert(perm[y]);
                    }
                } 
                if((*bef).f!=-inf) {
                    if(y-(*bef).f==subSize[(*bef).s]) {
                        wrongLoc[pr].erase((*bef).s);
                    } else {
                        wrongLoc[pr].insert((*bef).s);
                    }
                }
                if(wrongLoc[pr].size()) {
                    expectedLocation[pr]=-50;
                    problems.insert(pr);
                } else {
                    auto firstReal = actualChildrenLoc[pr].begin();
                    firstReal++;
                    expectedLocation[pr]=(*firstReal).f-1;
                    if(invPerm[pr]!=expectedLocation[pr]) {
                        problems.insert(pr);
                    } else {
                        problems.erase(pr);
                    }
                }
            }
            if(expectedLocation[perm[x]]!=x&&subSize[perm[x]]!=1) {
                problems.insert(perm[x]);
            } else {
                problems.erase(perm[x]);
            }
            if(expectedLocation[perm[y]]!=y&&subSize[perm[y]]!=1) {
                problems.insert(perm[y]);
            } else {
                problems.erase(perm[y]);
            }
            // cout << i << " " << x << " " << y << " " << problems << expectedLocation << wrongLoc << endl;
            // cout << "LINE 372 " << endl;
            // cout << i << " " << x << " " << y << " " << problems << " " << expectedLocation << " " << wrongLoc << endl;
            // cout << perm << invPerm << endl;
            if(problems.size()) {
                cout << "NO" << endl; 
            } else {
                cout << "YES" << endl;
            }
        }

        // cout << actualChildrenLoc << endl;
    }
    return 0;
}
/*
1
6 17
1 1 3 3 1
2 3 6 4 5 1
3 5
1 2
6 1
5 4
5 3
4 5
1 5
2 1
6 5
2 1
6 2
5 6
6 2
3 1
2 3
5 1
6 1
*/
/*
2 1 4 3 5 0
*/
/*
1
6 1
1 1 3 3 1
2 6 3 5 4 1
6 1
*/