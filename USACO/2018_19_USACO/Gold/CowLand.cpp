#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> tour1, tourDepth;
vector<int> first, subtreeSize, depth, last, pow2, parents;
vector<vector<int>> edges, sparseTable, lca;

class BIT {
    int n;
    vector<int> tree, data;

public:
    BIT(int n) : n(n + 5), data(n + 5), tree(n + 5) {}

    void set(int index, int value) {
        index++;
        int old = data[index];
        data[index] = value;
        while (index < n) {
            tree[index] ^= old ^ value;
            index += index & -index;
        }
    }

    int getXOR(int index) {
        int x = 0;
        index++;
        while (index > 0) {
            x ^= tree[index];
            index -= index & -index;
        }
        return x;
    }
};

void dfs(int node, int parent) {
    parents[node] = parent;
    int size = 1;
    if (node != 0) {
        depth[node] = depth[parent] + 1;
    }
    first[node] = tour1.size();
    if (node != 0 && edges[node].size() == 1) {
        tour1.push_back(node);
        tourDepth.push_back(depth[node]);
    }
    for (int neighbor : edges[node]) {
        if (neighbor != parent) {
            tour1.push_back(node);
            tourDepth.push_back(depth[node]);
            dfs(neighbor, node);
            tour1.push_back(node);
            tourDepth.push_back(depth[node]);
        }
    }
    subtreeSize[node] = size;
    last[node] = tour1.size() - 1;
    if (node != 0 && edges[node].size() == 1) {
        last[node] = tour1.size();
        tour1.push_back(node);
        tourDepth.push_back(depth[node]);
    }
}

int lc(int x, int y) {
    int i = min(first[x], first[y]);
    int j = max(first[x], first[y]) + 1;
    int pow = pow2[j - i];
    if (sparseTable[i][pow] < sparseTable[j - (1 << pow)][pow]) {
        return lca[i][pow];
    }
    return lca[j - (1 << pow)][pow];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    int n, q;
    cin >> n >> q;
    first=vector<int>(n);
    subtreeSize=vector<int>(n);
    parents=vector<int>(n);
    depth=vector<int>(n);
    last=vector<int>(n);
    edges=vector<vector<int>>(n);
    for (int i = 0; i < n; i++) {
        edges[i].clear();
    }

    vector<int> values(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    //cout << 107 << endl;
    dfs(0, -1);
    //cout << 109 << endl;
    BIT b(tour1.size());
    ///cout << 111 << endl;
    for (int i = 0; i < tour1.size(); i++) {
        b.set(i, values[tour1[i]]);
    }
    pow2.resize(tour1.size());
    int l = 1;
    for (int i = 0; i < 31; i++) {
        while ((1 << (i + 1)) > l && l < tour1.size()) {
            pow2[l] = i;
            l++;
        }
    }
    //cout << 123 << endl;
    sparseTable.resize(tour1.size());
    lca.resize(tour1.size());

    for (int i = 0; i < tour1.size(); i++) {
        sparseTable[i].push_back(tourDepth[i]);
        lca[i].push_back(tour1[i]);
    }

    for (int i = 1; (1 << i) <= tour1.size(); i++) {
        for (int j = 0; j <= tour1.size() - (1 << i); j++) {
            if (sparseTable[j][i - 1] < sparseTable[j + (1 << (i - 1))][i - 1]) {
                sparseTable[j].push_back(sparseTable[j][i - 1]);
                lca[j].push_back(lca[j][i - 1]);
            } else {
                sparseTable[j].push_back(sparseTable[j + (1 << (i - 1))][i - 1]);
                lca[j].push_back(lca[j + (1 << (i - 1))][i - 1]);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 2) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            int ll = lc(x, y);
            if (ll == 0) {
                cout << (b.getXOR(first[x]) ^ b.getXOR(first[y]) ^ b.getXOR(first[ll])) << "\n";
            } else {
                cout << (b.getXOR(first[x]) ^ b.getXOR(first[y]) ^ b.getXOR(first[ll]) ^ b.getXOR(first[parents[ll]])) << "\n";
            }
        } else {
            int index, value;
            cin >> index >> value;
            index--;
            b.set(first[index], value);
            b.set(last[index], value);
        }
    }

    return 0;
}