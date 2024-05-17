#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n, c;
    cin >> c >> n;
    int dist[1<<c];
    int values[n];
    deque<std::vector<int>> q;
    for(int i = 0; i < 1<<c; i++) {
        dist[i]=-1;
    }
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int value=0;
        for(int j = 0; j < c; j++) {
            if(s.at(j)=='G') {
                value += 1 << j;
            }
        }
        values[i]=value;
        vector<int> temp;
        temp.push_back(value);
        temp.push_back(1);
        q.push_back(temp);
        dist[value]=0;
    }
    while(q.size()>0) {
        vector<int> v =q.front(); 
        q.pop_front();
        for(int i = 0; i < c; i++) {
            int newVal = v[0]^(1<<i);
            if(dist[newVal]==-1) {
                dist[newVal]=v[1];
                vector<int> temp;
                temp.push_back(newVal);
                temp.push_back(v[1]+1);
                q.push_back(temp);
            }
        }
    }
    string ans = "";
    for(int i = 0; i < n; i++) {
        int dis = c-dist[values[i]^((1<<c)-1)];
        ans+=to_string(dis)+"\n";
    }
    cout << ans;
}