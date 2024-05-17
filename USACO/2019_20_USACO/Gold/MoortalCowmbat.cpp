#include <iostream>
#include <vector>
#include <deque>   
int n,m,k;
using namespace std;
using ll = long long;
using pi = pair<int, int>;
bool possible(vector<vector<int>> &changeCost, int test, int i, int j) {
    if(i==j) {
        //cout << "true by line 11" << endl;
        return true;
    }
    int earliestVisit[m];
    for(int l = 0; l < m; l++) {
        if(l==i) {
            earliestVisit[l] = 0;
        } else {
            earliestVisit[l]=10000;
        }
    }
    deque<pi> q;
    pi start(i, 0);
    q.push_back(start);
    while(q.size()>0) {
        pi temp = q.front();
        //cout << "pair: " << temp.first << " " << temp.second << " what is tested: " << test << " i: " << i << " j: " << j << endl;
        q.pop_front();
        for(int l = 0; l < m; l++) {
            //cout << "temp: " << temp.first << " " << temp.second << " l: " << l << " cost: " << changeCost[temp.first][l] << " earliestVisit: " << earliestVisit[l] << endl;
            //cout << temp.second << " " << changeCost[temp.first][l] << " " << temp.second+changeCost[temp.first][l] << " " << test << " " << (temp.second+changeCost[temp.first][l]<=test) << endl;
            if(temp.second+changeCost[temp.first][l]<=test&&earliestVisit[l]>temp.second+changeCost[temp.first][l]) {
                //cout << "got here " << endl;
                earliestVisit[l] = temp.second+changeCost[temp.first][l];
                if(l==j)  {
                    //cout << "true by line 22" << endl;
                    return true;
                }
                pi tem(l, temp.second+changeCost[temp.first][l]);
                q.push_back(tem);
            }
        }
    }
    //cout << "false by line 31" << endl;
    return false;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);

    string s;
    cin >> n >> m >> k >> s;
    vector<vector<int>> changeCost(m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            int temp;
            cin >> temp;
            changeCost[i].push_back(temp);
        }
    }
    int minChangeCost[m][m];
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            int lo = 0;
            int hi = changeCost[i][j];
            while(lo+1<hi) {
                int mid = (lo+hi)/2;
                if(possible(changeCost, mid, i, j)) {
                    hi = mid;
                } else {
                    lo=mid;
                }
            }
            //cout << "i: " << i << " j: " << j << " lo: " << lo << " hi: " << hi << endl;
            if(possible(changeCost, lo, i, j)) {
                minChangeCost[i][j] = lo;
            } else {
                minChangeCost[i][j] = hi;
            }
        }
    }
    /*
    cout << "INITIAL PRICES" << endl;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            cout << changeCost[i][j] << " ";
        }
        cout << endl;
    }

    cout << "LOWEST PRICES" << endl;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            cout << minChangeCost[i][j] << " ";
        }
        cout << endl;
    }
        */
    int prefSum[n+1][m];
    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= n; j++) {
            //cout << s[j-1]-'a' << endl;
            if(j==0) {
                prefSum[j][i]=0;
                continue;
            }
            prefSum[j][i] = prefSum[j-1][i] + minChangeCost[s[j-1]-'a'][i];
        }
    }
    /*
    cout << endl;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j <= n; j++) {
            cout << prefSum[j][i] << " ";
        }
        cout << endl;
    }
    */
    int minCost[n];
    for(int i = 0; i < n; i++) {
        minCost[i]=1000000000;
    }
    int function[n][m];
    for(int i = 0; i < m; i++) {
        function[k-1][i]=prefSum[k][i];
        minCost[k-1]=min(minCost[k-1], function[k-1][i]);
    }
    for(int i = k; i < n; i++) {
        for(int j = 0; j < m; j++) {
            function[i][j] = function[i-1][j] + minChangeCost[s[i]-'a'][j];
            if(i-k+1>=k) {
                function[i][j]=min(function[i][j], minCost[i-k]+prefSum[i+1][j]-prefSum[i-k+1][j]);
            }
            minCost[i] = min(minCost[i], function[i][j]);
        }
    }
    cout << minCost[n-1] << endl;
}