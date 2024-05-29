#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
void dfs(int i, bool visited2[], int function[][2], vector<vector<int>> &destinations) {
    //cout << "line 9: " << i << endl;
    function[i][1]=function[i][0];
    visited2[i]=true;
    for(int x: destinations[i]) {
        if(function[x][0]>function[i][0]) {
            if(!visited2[x]) {
                dfs(x, visited2, function, destinations);
            }
            function[i][1]=min(function[i][1], function[x][1]);
        } else {
            function[i][1]=min(function[i][1], function[x][0]);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    string ans = "";
    int t;
    cin >> t;
    for(;t>0;t--) {
        int n,m;
        cin >> n >> m;
        //cout << n << m << endl;
        vector<vector<int>> destinations(n);
        for(int i = 0; i < m; i++) {
            int a,b;
            cin >> a >> b;
            a--;
            b--;
            destinations[a].push_back(b);
        }
        int function[n][2];
        function[0][1]=function[0][0]=0;
        queue<int> q;
        bool visited[n] = {false};
        visited[0]=true;
        q.push(0);
        while(q.size()>0) {
            int tem = q.front();
            q.pop();
            for(int i: destinations[tem]) {
                if(visited[i]) continue;
                visited[i]=true;
                function[i][0]=function[tem][0]+1;
                q.push(i);
            }
        }
        bool visited2[n] = {false};
        visited2[0]=true;
        /*
        for(int i = 1; i < n; i++) {
            if(visited2[i]) continue;
            dfs(i, visited2, function, destinations);
        }
        */
        dfs(0, visited2, function, destinations);
        //cout << endl;
        for(int i = 0; i < n-1; i++) {
            ans+=to_string(function[i][1])+" ";
        }
        ans+=to_string(function[n-1][1]) + "\n";
    }
    std::cout << ans;
}