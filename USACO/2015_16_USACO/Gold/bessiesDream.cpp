#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

struct State {
    int x, y, moves, direction, orange;

    State(int x, int y, int moves, int direction, int orange) {
        this->x = x;
        this->y = y;
        this->moves = moves;
        this->direction = direction;
        this->orange = orange;
    }
};

int n, m;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

bool outOfBounds(int x, int y) {
    return x < 0 || y < 0 || x >= n || y >= m;
}

int main() {
    freopen("dream.in", "r", stdin);
    //freopen("dream.out", "w", stdout);
    cin >> n >> m;
    vector<vector<vector<vector<bool>>>> visited(n, vector<vector<vector<bool>>>(m, vector<vector<bool>>(4, vector<bool>(2))));
    vector<vector<int>> grid(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    queue<State> q;
    q.push(State(0, 0, 0, 0, 0));
    visited[0][0][0][0] = true;
    while (!q.empty()) {
        State s = q.front();
        q.pop();

        if (s.x == n - 1 && s.y == m - 1) {
            cout << s.moves << endl;
            return 0;
        }
        bool freeMove = false;
        if (grid[s.x][s.y] == 4) {
            if (outOfBounds(s.x + dx[s.direction], s.y + dy[s.direction])) {
                freeMove = true;
            } else {
                int newx = s.x + dx[s.direction];
                int newy = s.y + dy[s.direction];
                if (grid[newx][newy] == 0 || (grid[newx][newy] == 3 && s.orange == 0)) {
                    freeMove = true;
                } else {
                    visited[newx][newy][s.direction][grid[newx][newy] == 2 ? 1 : 0] = true;
                    q.push(State(newx, newy, s.moves + 1, s.direction, grid[newx][newy] == 2 ? 1 : 0));
                }
            }
        }

        if (grid[s.x][s.y] == 1 || grid[s.x][s.y] == 2 || grid[s.x][s.y] == 3 || freeMove) {
            for (int i = 0; i < 4; i++) {
                int newx = s.x + dx[i];
                int newy = s.y + dy[i];
                if (outOfBounds(newx, newy)) continue;

                if (grid[newx][newy] == 1) {
                    if (!visited[newx][newy][i][s.orange]) {
                        visited[newx][newy][i][s.orange] = true;
                        q.push(State(newx, newy, s.moves + 1, i, s.orange));
                    }
                } else if (grid[newx][newy] == 2) {
                    if (!visited[newx][newy][i][1]) {
                        visited[newx][newy][i][1] = true;
                        q.push(State(newx, newy, s.moves + 1, i, 1));
                    }
                } else if (grid[newx][newy] == 3 && s.orange == 1) {
                    if (!visited[newx][newy][i][1]) {
                        visited[newx][newy][i][1] = true;
                        q.push(State(newx, newy, s.moves + 1, i, 1));
                    }
                } else if (grid[newx][newy] == 4) {
                    if (!visited[newx][newy][i][0]) {
                        visited[newx][newy][i][0] = true;
                        q.push(State(newx, newy, s.moves + 1, i, 0));
                    }
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}