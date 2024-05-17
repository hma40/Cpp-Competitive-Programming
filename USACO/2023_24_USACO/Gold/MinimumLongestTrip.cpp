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

using namespace std;
bool debug = true;
vector<map<pair<int, int>, bool>> maps;
vector<int> nextNode;
vector<long long> firstMove;
vector<int> travSize;
void printArray(vector<int> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
bool lesse(int a, int b) {
    pair<int, int> temp = {a,b};
    pair<int, int> temp2 = {b,a};
    if(maps[travSize[a]].count(temp)) {
        return maps[travSize[a]][temp];
    }
    if(maps[travSize[a]].count(temp2)) {
        return !maps[travSize[a]][temp2];
    }
    if(nextNode[a]==-1) {
        maps[travSize[a]][temp]=false;
    }
    if(firstMove[a]!=firstMove[b]) {
        if(firstMove[a]<firstMove[b]) {
            maps[travSize[a]][temp]=true;
            return true;
        }
        maps[travSize[a]][temp]=false;
        return false;
    }
    bool ret = lesse(nextNode[a], nextNode[b]);
    maps[travSize[a]][temp]=ret;
    return ret;
}
int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, long>>> invadj(n);
    vector<vector<pair<int, long>>> adj(n);
    vector<int> indeg(n);

    int maxTrav = 0;

    for (int i = 0; i < m; ++i) {
        int start, end, size;
        cin >> start >> end >> size;
        --start;
        --end;
        invadj[end].emplace_back(start, size);
        ++indeg[start];
        adj[start].emplace_back(end, size);
    }
    travSize.resize(n);
    deque<pair<int, int>> q;
    vector<int> topo;
    firstMove = vector<long long>(n, 0);
    nextNode = vector<int>(n, -1);

    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) q.push_back({i,i});
    }

    while (!q.empty()) {
        pair<int, int> x = q.front();
        q.pop_front();

        if (x.first != x.second) {
            travSize[x.second] = travSize[x.first] + 1;
        }

        maxTrav = max(maxTrav, travSize[x.second]);
        topo.push_back(x.second);

        for (const pair<int, long long>& y : invadj[x.second]) {
            if (--indeg[y.first] == 0) {
                q.emplace_back(x.second, y.first);
            }
        }
    }
    maps.resize(maxTrav+1);
    vector<long long> ans(n);

    for (int i : topo) {
        long long bestFirstMove = LLONG_MAX;
        vector<int> potentials;

        for (const pair<int, long>& j : adj[i]) {
            if (travSize[j.first] == travSize[i] - 1) {
                if (j.second < bestFirstMove) {
                    bestFirstMove = j.second;
                    potentials.clear();
                    potentials.push_back(j.first);
                } else if (j.second == bestFirstMove) {
                    potentials.push_back(j.first);
                }
            }
        }
        // cout << i << endl;
        // printArray(potentials);
        if (!potentials.empty()) {
            firstMove[i] = bestFirstMove;
            int bestFirstNode = potentials[0];
            for (int x = 1; x < potentials.size(); ++x) {
                if (lesse(potentials[x], bestFirstNode)) {
                    bestFirstNode = potentials[x];
                }
            }
            nextNode[i] = bestFirstNode;
            ans[i] = ans[bestFirstNode] + bestFirstMove;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << travSize[i] << " " << ans[i] << "\n";
    }
    // for(auto a: maps) {
    //     for(auto b: a) {
    //         cout << b.first.first << " " << b.first.second << " " << b.second << endl;
    //     }
    //     cout << endl;
    // }
    return 0;
}