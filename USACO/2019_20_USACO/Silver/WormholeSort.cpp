#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <deque>

using namespace std;

struct wormhole {
    int destination, size;
    bool operator<(wormhole other) {
        if(other.size>size) {
            return false;
        }
        return true;
    }
};

bool possible(int n, int m, int num, int needGo[], vector<vector<wormhole>> wormholes) {
    //cout << "line 18: " << num << endl;
    bool visited[n];
    for(int i = 0; i < n; i++) {
        visited[i]=false;
    }
    for(int i = 0; i < n; i++) {
        if(visited[i]) continue;
        if(needGo[i]==-1) continue;
        unordered_set<int> here;
        here.insert(i);
        visited[i]=true;
        deque<int> q;
        q.push_back(i);
        //cout << "got to line 27";
        while(q.size()>0) {
            int x = q.front();
            //cout << "in queue: " << x << endl;
            q.pop_front();
            for(int j = 0; j < wormholes[x].size(); j++) {
                if(wormholes[x][j].size<num) {
                    break;
                }
                if(visited[wormholes[x][j].destination]) {
                    continue;
                }
                visited[wormholes[x][j].destination]=true;
                q.push_back(wormholes[x][j].destination);
                if(needGo[wormholes[x][j].destination]!=-1) {
                    here.insert(wormholes[x][j].destination);
                }
            }
        }
        for(int x: here) {
            if(here.count(needGo[x])==0) {
                return false;
            }
        }
    }
    return true;
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //cout << "got here";
    int n,m;
    vector<vector<wormhole>> wormholes;
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    cin >> n >> m;
    //cout << "n:m" << n << "," << m << endl;
    int needGo[n];
    for(int i = 0; i < n; i++) {
        needGo[i]=-1;
    }
    //cout << n << m;
    bool needChange=false;
    for(int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        temp--;
        if(temp!=i) {
            needChange=true;
            needGo[i]=temp;
        }
    }
    if(!needChange) {
        cout << -1;
        return 0;
    }
    for(int i = 0; i < n; i++) {
        vector<wormhole> temp;
        wormholes.push_back(temp);
    }
    //cout << "here " << 2 << endl;
    for(int i = 0; i < m; i++) {
        //cout << "i:" << i << " m:" << m << endl;
        int a,b,c;
        cin >> a >> b >> c;
        a--;
        b--;
        wormhole temp1, temp2;
        temp1.destination=b;
        temp1.size=c;
        temp2.destination=a;
        temp2.size=c;
        wormholes[a].push_back(temp1);
        wormholes[b].push_back(temp2);
    }
    for(int i = 0; i < n; i++) {
        sort(begin(wormholes[i]), end(wormholes[i]));
    }
    //cout << "got here";
    int low = 0;
    int high = 1e9+2;
    while(low+1<high) {
        int mid = low+(high-low)/2;
        //cout << low << " "<<mid<<" "<<high << endl;
        if(possible(n, m, mid, needGo, wormholes)) {
            low=mid;
        } else {
            high=mid;
        }
    }
    if(possible(n, m, high, needGo, wormholes)) {
        cout << high;
    } else {
        cout << low;
    }
    return 0;
}