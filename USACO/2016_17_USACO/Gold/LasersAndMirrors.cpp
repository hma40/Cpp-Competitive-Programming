#include <bits/stdc++.h>

using namespace std;

struct Fence {
    int x, y, index, compressX, compressY;
    Fence(int xx, int yy, int iindex) {
        x=xx;
        y=yy;
        index=iindex;
        compressX=compressY=0;
    }
};

struct State {
    bool fromX;
    int x, y, index, compressX, compressY;
    int mirrors;
    State(bool ffromX, int xx, int yy, int iindex, int ccompressX, int ccompressY, int mmirrors) {
        fromX=ffromX;
        x=xx;
        y=yy;
        index=iindex;
        compressX=ccompressX;
        compressY=ccompressY;
        mirrors=mmirrors;
    }
};
void print_fence(Fence &f) {
    cout << f.x << " " << f.y << " " << f.index << " " << f.compressX << " " << f.compressY << endl;
}
int main() {
    int n;

    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    cin >> n;
    //freopen("lasers.in", "r", stdin);
	//freopen("lasers.out", "w", stdout);
    int laserX, laserY, barnX, barnY;
    cin >> laserX >> laserY >> barnX >> barnY;
    //cout << n << endl;
    //cout << laserX << " " << laserY << " " << barnX << " " << barnY << endl;
    vector<vector<Fence>> xComp(n + 2);
    vector<vector<Fence>> yComp(n + 2);
    vector<Fence> fences;
    fences.push_back(Fence(laserX, laserY, 0));
    fences.push_back(Fence(barnX, barnY, 1));
    //print_fence(fences[0]);
    //print_fence(fences[1]);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        fences.push_back(Fence(x, y, i + 2));
    }
    
    sort(fences.begin(), fences.end(), [](const Fence& f1, const Fence& f2)->bool{
        return f1.x < f2.x;
    });
    //cout << "Got here 0" << endl;
    xComp[0].push_back(fences[0]);
    for (int i = 1; i < fences.size(); i++) {
        if (fences[i].x == fences[i - 1].x) {
            fences[i].compressX = fences[i - 1].compressX;
        } else {
            fences[i].compressX = fences[i - 1].compressX + 1;
        }
        //xComp[fences[i].compressX].push_back(fences[i]);
    }
    
    sort(fences.begin(), fences.end(), [](const Fence& f1, const Fence& f2) ->bool {
        return f1.y < f2.y;
    });

    yComp[0].push_back(fences[0]);
    for (int i = 1; i < fences.size(); i++) {
        if (fences[i].y == fences[i - 1].y) {
            fences[i].compressY = fences[i - 1].compressY;
        } else {
            fences[i].compressY = fences[i - 1].compressY + 1;
        }
        //yComp[fences[i].compressY].push_back(fences[i]);
    }
    //cout << "Got here" << endl;
    vector<bool> visitedX(n + 2, false);
    vector<bool> visitedY(n + 2, false);
    visitedX[0] = visitedY[0] = true;
    deque<State> q;
    sort(begin(fences), end(fences), [](const Fence a, const Fence b) -> bool {
        return a.index<b.index;
    });
    for(int i = 0; i < n+2; i++) {
        xComp[fences[i].compressX].push_back(fences[i]);
        yComp[fences[i].compressY].push_back(fences[i]);
    }
    for (const Fence& f : xComp[fences[0].compressX]) {
        if (!visitedX[f.index]) {
            visitedX[f.index] = true;
            //cout << f.x << " " << f.y << " " << f.index << " " << f.compressX << " " << f.compressY << endl;
            q.push_back(State(true, f.x, f.y, f.index, f.compressX, f.compressY, 0));
        }
    }

    for (const Fence& f : yComp[fences[0].compressY]) {
        if (!visitedY[f.index]) {
            visitedY[f.index] = true;
            //cout << f.x << " " << f.y << " " << f.index << " " << f.compressX << " " << f.compressY << endl;
            q.push_back(State(false, f.x, f.y, f.index, f.compressX, f.compressY, 0));
        }
    }

    while (!q.empty()) {
        State s = q.front();
        q.pop_front();
        //  cout << s.fromX << " " << s.x << " " << s.y << " " << s.index << " " << s.compressX << " " << s.compressY << " " << s.mirrors << endl;
        if (s.index == 1) {
            cout << s.mirrors << endl;
            return 0;
        }

        if (s.fromX) {
            for (const Fence& f : yComp[s.compressY]) {
                if (!visitedY[f.index]) {
                    visitedY[f.index] = true;
                    q.push_back(State(false, f.x, f.y, f.index, f.compressX, f.compressY, s.mirrors + 1));
                }
            }
        } else {
            for (const Fence& f : xComp[s.compressX]) {
                if (!visitedX[f.index]) {
                    visitedX[f.index] = true;
                    q.push_back(State(true, f.x, f.y, f.index, f.compressX, f.compressY, s.mirrors + 1));
                }
            }
        }
    }

    cout << -1 << endl;

    return 0;
}