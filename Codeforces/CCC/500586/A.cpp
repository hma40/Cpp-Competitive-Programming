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
void printArray(vector<char> &v) {
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
void printArray(vector<vector<char>> &v) {
    if(debug) {
        cout << "{\n";
        trav(y, v) printArray(y);
        cout << "}" << endl;
    }
}
int n,m;
int toNodeNum(pi coords) {
    return coords.f*m+coords.s;
}
pi toCoords(int nodeNum) {
    return {nodeNum/m, nodeNum%m};
}
bool inBounds(int r, int c) {
    return r>=0&&c>=0&&r<n&&c<m;
}
int toNodeNum(int r, int c) {
    return toNodeNum({r,c});
}
vector<vector<int>> adj;
vector<vector<int>> reward;
ll dfs(int node) {
    pi coords = toCoords(node);
    ll sumChildren = 0;
    trav(neigh, adj[node]) {
        sumChildren+=dfs(neigh);
    }
    if(sumChildren+reward[coords.f][coords.s]>0) {
        return sumChildren+reward[coords.f][coords.s];
    }
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);

    cin >> n >> m;
    vector<vector<char>> dominoes(n, vector<char>(m));
    F0R(i, n) {
        string s;
        cin >> s;
        F0R(j, m) {
            dominoes[i][j]=s[j];    
        }
    }
    reward.resize(n, vector<int>(m));
    F0R(i, n) {
        F0R(j, m) {
            cin >> reward[i][j];
        }
    }
    pi start = {0,0};
    F0R(i, n) {
        F0R(j, m) {
            if(dominoes[i][j]=='.') start={i,j};
        }
    }
    adj.resize(n*m);
    F0R(i, n) {
        F0R(j, m) {
            if(inBounds(i+1, j)) {
                if(dominoes[i+1][j]=='^') {
                    adj[toNodeNum(i, j)].add(toNodeNum(i+2,j));
                }
            }
            if(inBounds(i-1, j)) {
                if(dominoes[i-1][j]=='v') {
                    adj[toNodeNum(i, j)].add(toNodeNum(i-2,j));
                }
            }
            if(inBounds(i, j+1)) {
                if(dominoes[i][j+1]=='<') {
                    adj[toNodeNum(i, j)].add(toNodeNum(i,j+2));
                }
            }
            if(inBounds(i, j-1)) {
                if(dominoes[i][j-1]=='>') {
                    adj[toNodeNum(i, j)].add(toNodeNum(i,j-2));
                }
            }
        }
    }

    cout << dfs(toNodeNum(start)) << endl;
    return 0;
}