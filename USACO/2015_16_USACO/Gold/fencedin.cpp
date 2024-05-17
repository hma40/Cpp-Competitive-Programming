#include <bits/stdc++.h>

using namespace std;

int n, m;

struct Edge {
    int a, b, c;
    Edge(int a, int b, int c) : a(a), b(b), c(c) {}
};

class DisjointSets {
public:
    int n;
    vector<int> parents, sizes;

    DisjointSets(int n) : n(n), parents(n, -1), sizes(n, 1) {}

    int find(int a) {
        if (parents[a] == -1)
            return a;
        return parents[a] = find(parents[a]);
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (sizes[a] > sizes[b]) {
                parents[b] = a;
                sizes[a] += sizes[b];
            } else {
                parents[a] = b;
                sizes[b] += sizes[a];
            }
        }
    }
};

int calc(int a, int b) {
    return a * m + b;
}

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);
    int A, B;
    cin >> A >> B >> n >> m;

    vector<int> horiz(n + 2);
    vector<int> vert(m + 2);

    horiz[n + 1] = 0;
    horiz[n] = A;
    vert[m + 1] = 0;
    vert[m] = B;

    for (int i = 0; i < n; i++) {
        cin >> horiz[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> vert[i];
    }

    sort(horiz.begin(), horiz.end());
    sort(vert.begin(), vert.end());

    n++;
    m++;

    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + 1 < n) {
                edges.push_back(Edge(calc(i, j), calc(i + 1, j), vert[j + 1] - vert[j]));
            }
            if (j + 1 < m) {
                edges.push_back(Edge(calc(i, j), calc(i, j + 1), horiz[i + 1] - horiz[i]));
            }
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge &x, const Edge &y) {
        return x.c < y.c;
    });

    long long ans = 0;
    DisjointSets ds(n * m);
    for (const Edge &e : edges) {
        if (!ds.connected(e.a, e.b)) {
            ans += e.c;
            ds.unite(e.a, e.b);
        }
    }

    cout << ans << endl;

    return 0;
}