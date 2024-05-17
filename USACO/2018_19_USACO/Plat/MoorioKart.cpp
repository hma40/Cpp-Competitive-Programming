#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <deque>
#include <time.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
ll mod = 1000000007;

    int ad(int a, int b) { return (a+b)%mod; }
    int sub(int a, int b) { return (a-b+mod)%mod; }
    int mul(int a, int b) { return (ll)a*b%mod; }
    int MUL(int& a, int b) { return a = mul(a,b); }
pi operator+(const pi& l, const pi& r) {
    return {ad(l.first,r.first),ad(l.second,r.second)};
}
 
pi operator+=(pi& l, const pi& r) {
    return l=l+r;
}
pi comb(pi a, pi b) {
    return {ad(mul(a.first,b.second),mul(a.second,b.first)),mul(a.second,b.second)};
}
void print_map(std::unordered_map<int, pi> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second.first << " " << pair.second.second << "}\n";
    }
}
struct farm {
    vector<int> meadows;
    map<int, pi> distances;
};
vector<farm> farms;
int n,m,x,y;

vector<vector<pi>> roads;
int main() {
    clock_t cSt, cFin;
    clock_t clockStart, clockFinish;

    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("mooriokart.in", "r", stdin);
    freopen("mooriokart.out", "w", stdout);
    cSt = clock();
    cin >> n >> m >> x >> y;
    for(int i = 0; i < n; i++) {
        vector<pi> temp;
        roads.push_back(temp);
    }
    for(int i = 0; i < m; i++) {
        int a,b,d;
        cin >> a >> b >> d;
        a--;
        b--;
        pi firstPair(a, d);
        pi secondPair(b, d);
        roads[a].push_back(secondPair);
        roads[b].push_back(firstPair);
    }
    bool visited[n];
    for(int i = 0; i < n; i++) visited[i]=false;
    clockStart=clock();
    for(int i = 0; i < n; i++) {

        if(visited[i]) continue;
        //cout << i << " got here\n";
        deque<int> q;
        q.push_back(i);
        //cout << "got here " << i << endl;
        visited[i]=true;
        farm f;
        f.meadows.push_back(i);
        while(q.size()>0) {
            int xx = q.front();
            q.pop_front();
            for(pi x: roads[xx]) {
                if(visited[x.first]) continue;
                visited[x.first]=true;
                q.push_back(x.first);
                f.meadows.push_back(x.first);
            }

        }
        farms.push_back(f); 
    }
    clockFinish=clock();
   // cout << (clockFinish-clockStart) << endl; 
    //cout << farms.size() << endl;
    int maxThing = y - x * (ll)farms.size();
    if(maxThing<0) maxThing=0;

    //for(vector<pi> p: roads[2])
    clockStart=clock();
    for(int aa = 0; aa < farms.size(); aa++) {
        farm &f = farms[aa];
        for(int i: f.meadows) {
            vector<bool> visited(n);
            visited[i]=true;
            deque<pi> q;
            pi tempo(i, 0);
            q.push_back(tempo);
            while(q.size()) {
                pi xx = q.front();
                q.pop_front();
                if(xx.first>i) {
                    //if(xx.second==0) cout << xx.first << " " << i << endl;
                    int s = min(xx.second, maxThing);
                    f.distances[s]+={xx.second, 1};
                }
                for(pi j: roads[xx.first]) {
                    if(visited[j.first]) continue;
                    visited[j.first]=true;
                    pi temp(j.first, xx.second+j.second);
                    q.push_back(temp);
                }
            }
        }
    }   
    clockFinish=clock();
    //cout << (clockFinish-clockStart) << endl; 
    //unordered_map<ll, pi> thingies = farms[0].distances;
    pi abc[y+1];
    for(int i = 0; i <= y; i++) {
        abc[i]=farms[0].distances[i];
    }
    
    for(int i = 1; i < farms.size(); i++) {
        vector<pi> temp(y+1);

        //cout << thingies.size() << " " << farms[i].distances.size() << endl;
        clockStart=clock();
        for(auto yy: farms[i].distances) {
            for(int jj = 0; jj <= y; jj++) {
                //int te = ;
                temp[min(maxThing, jj+yy.first)]+=comb(abc[jj], yy.second);
            }
        }
        clockFinish=clock();
        //cout << (clockFinish-clockStart)  << endl;
        for(int jj = 0; jj <= y; jj++) abc[jj]=temp[jj];
        //for(pi x: thingies) cout << x.first << " " << x.second << endl;
    }
                
    //print_map(thingies);
    //ll ans = 0;
    ll ans = abc[maxThing].first;
    //std::cout << maxThing << " " << "GOT HERE" << ans << endl;
    ll temp1 = abc[maxThing].second % mod * x % mod * farms.size() % mod;
    ans+=temp1;
    ans%=mod;
    //cout << "ans: " << ans << endl;
    //cout << farms.size() << endl;
    for(int i = farms.size()-1; i > 0; i--) {
        ans*=i;
        ans%=mod;
        ans*=2;
        ans%=mod;
        //cout << "i: " << i << " ans: " << ans << endl;
    }

    std::cout << ans << endl;
    cFin=clock();
    //cout << cFin - cSt << endl;
}
/*
8 5 1 0
1 2 2
2 3 3
4 5 4
6 7 5
7 8 6
*/