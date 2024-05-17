#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct movie {
    int duration;
    int showtimes;
    vector<int> startTimes;
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
    int n,l;
    cin >> n >> l;
    vector<movie> movies(n);
    for(int i = 0; i < n; i++) {
        cin >> movies[i].duration >> movies[i].showtimes;
        movies[i].startTimes=vector<int>(movies[i].showtimes);
        for(int j = 0; j < movies[i].showtimes; j++) {
            cin >> movies[i].startTimes[j];
        }
    }
    vector<int> arr(1<<n, -1);
    arr[0]=0;
    int ans = 50;
    for(int i = 1; i < 1<<n; i++) {
        for(int j = 0; j < n; j++) {
            if((i&(1<<j))!=0) {
                if(arr[i^(1<<j)]<0) continue;
                int movIndex = lower_bound(begin(movies[j].startTimes), end(movies[j].startTimes), arr[i^(1<<j)])-begin(movies[j].startTimes);
                if(movIndex==movies[j].startTimes.size()||movies[j].startTimes[movIndex]!=arr[i^(1<<j)]) {
                    movIndex--;
                }
                if(movIndex<0) {
                    continue;                   
                }
                int newTime = min(l, movies[j].startTimes[movIndex]+movies[j].duration);
                arr[i]=max(arr[i], newTime);
            }
        }
    }
    for(int i = 0; i < 1<<n; i++) {
        if(arr[i]==l) {
            int here = 0;
            for(int j = 0; j < n; j++) {
                if((i&(1<<j))!=0) here++; 
            }
            ans=min(ans, here);
        }
    }
    if(ans==50) cout << -1 << endl;
    else cout << ans << endl; 
}