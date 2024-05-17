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
ll mod = 1000000007;
bool debug = true;
vector<string> split(string s, char delimiter) {
    vector<string> ret;
    ret.push_back("");
    F0R(i, s.length()) {
        if(s[i]==delimiter) {
            ret.add("");
        } else {
            ret.back()+=s[i];
        }
    }
    return ret;
}
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
void printArray(vector<int> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<ll> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<bool> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<string> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<vector<int>> &v) {
    if(debug) {
        cout << "{\n";
        trav(y, v) printArray(y);
        cout << "}" << endl;
    }
}
/*
hash function
INFO:
current node
status of each stall (0: unvisited, 1: key taken, 2: key placed)
result: current node + (each stall)*1000000007^stall number (mod 2^61-1)
*/
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("a.in", "r", stdin);
    //freopen("a.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays
    int t;
    cin >> t;
    while(t--) {
        int n,m;
        cin >> n >> m;
        vector<int> stallColors(n), initialKeys(n), finalKeys(n);
        vector<vector<int>> adj(n);
        F0R(i, n) cin >> stallColors[i];
        F0R(i, n) cin >> initialKeys[i];
        F0R(i, n) cin >> finalKeys[i];
        F0R(i, n) {
            stallColors[i]--;
            initialKeys[i]--;
            finalKeys[i]--;
        }
        F0R(i, m) {
            int a,b;
            cin >> a >> b;
            adj[--a].add(--b);
            adj[b].add(a);
        }
        vector<bool> visited(n);
        visited[0]=true;
        vector<bool> hasKey(n);
        deque<int> q;
        q.add(0);
        vector<set<int>> couldVisit(n);
        while(q.size()) {
            int x = q.front();
            //cout << x << endl;
            q.pop_front();
            hasKey[initialKeys[x]]=true;
            trav(x, couldVisit[initialKeys[x]]) {
                if(!visited[x]) {
                    visited[x]=true;
                    q.add(x);
                }
            }
            couldVisit[initialKeys[x]].clear();
            trav(y, adj[x]) {
                if(!visited[y]) {
                    if(hasKey[stallColors[y]]) {
                        visited[y]=true;
                        q.add(y);
                    } else {
                        couldVisit[stallColors[y]].insert(y);
                    }
                }
            }
        }
        bool fail = false;
        F0R(x, n) {
            //cout << x << " " << visited[x] << " " << initialKeys[x] << " " << finalKeys[x] << endl;
            if(!visited[x]&&initialKeys[x]!=finalKeys[x]) {
                cout << "NO" << endl;
                fail=true;
                break;
            }
        }
        //printArray(visited);
        if(fail) continue;
        vector<bool> hasKey2(n);
        vector<bool> visited2(n);
        q.add(0);
        visited2[0]=true;
        while(q.size()) {
            int x = q.front();
            // cout << "133 " << x << endl;
            // cout << "-------" << endl; 
            // F0R(i, n) {
            //     cout << i << " ";
            //     trav(j, couldVisit[i]) {
            //         cout << j << " ";
            //     }
            //     cout << endl;
            // }
            //cout << "-------" << endl;
            q.pop_front();
            hasKey2[finalKeys[x]]=true;
            //printArray(hasKey2);
            //printArray(visited2);
            trav(x, couldVisit[finalKeys[x]]) {
                if(!visited2[x]) {
                    visited2[x]=true;
                    //cout << "ADDING FROM LINE 144 " << x << endl;
                    q.add(x);
                }
            }
            couldVisit[finalKeys[x]].clear();
            trav(y, adj[x]) {
                if(!visited2[y]&&visited[y]) { 
                    if(hasKey2[stallColors[y]]||finalKeys[y]==stallColors[y]) {
                        visited2[y]=true;
                        //cout << "ADDING FROM LINE 153: " << y << endl;
                        q.add(y);
                    } else {
                        couldVisit[stallColors[y]].insert(y);
                    }
                }
            }
        }
        F0R(x, n) {
            if(!visited2[x]&&initialKeys[x]!=finalKeys[x]) {
                fail=true;
                cout << "NO" << endl;
                break;
            }
        }
        if(!fail) cout << "YES" << endl;
    }
    return 0;
}