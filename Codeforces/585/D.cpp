#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll pow3[15];
struct score {
    pair<ll, ll> mw;
    ll add; 
    ll index;
};
vector<score> firstHalf, secondHalf;
int ub(pair<ll, ll> need) {
    int lo = 0;
    int hi = secondHalf.size();
    while(lo+1<hi) {
        int mid = (lo+hi)/2;
        if(secondHalf[mid].mw<=need) {
            lo=mid;
        } else {
            hi=mid;
        }
    }
    if(secondHalf[lo].mw<=need) return hi-1;
    return lo-1;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    pow3[0]=1;
    for(int i = 1; i < 15; i++) {
        pow3[i]=pow3[i-1]*3;
    }
    int n;
    cin >> n;
    int scores[n][3];
    for(int i = 0; i < n; i++) {
        cin >> scores[i][0] >> scores[i][1] >> scores[i][2];
    }

    for(int i = 0; i < pow3[n/2]; i++) {
        int temp = i;
        ll curScore[3]={0};
        for(int j = 0; j < n/2; j++) {
            int notParticip = temp%3;
            temp/=3;
            for(int k = 0; k < 3; k++) {
                if(k==notParticip) continue;
                curScore[k]+=scores[j][k];
            } 
        }
        curScore[1]-=curScore[0];
        curScore[2]-=curScore[0];
        score tmp;
        tmp.mw=make_pair(curScore[1], curScore[2]);
        tmp.add=curScore[0];
        firstHalf.push_back(tmp);
    }
    for(int i = 0; i < pow3[n-n/2]; i++) {
        int temp = i;
        ll curScore[3]={0};
        for(int j = n/2; j < n; j++) {
            int notParticip = temp%3;
            temp/=3;
            for(int k = 0; k < 3; k++) {
                if(k==notParticip) continue;
                curScore[k]+=scores[j][k];
            } 
        }
        curScore[1]-=curScore[0];
        curScore[2]-=curScore[0];
        score tmp;
        tmp.mw=make_pair(curScore[1], curScore[2]);
        tmp.add=curScore[0];
        tmp.index=i;
        secondHalf.push_back(tmp);
    }
    sort(begin(secondHalf), end(secondHalf), [](const score &a, const score &b) -> bool{
        if(a.mw==b.mw) return a.add<b.add;
        return a.mw<b.mw;
    });
    ll bestScore = -1e18;
    int bestLIndex = -1;
    int bestRIndex = -1;
    for(int i = 0; i < firstHalf.size(); i++) {
        score s = firstHalf[i];
        pair<ll, ll> tmp = make_pair(-s.mw.first, -s.mw.second);
        int ubb = ub(tmp);
        if(secondHalf[ubb].mw==tmp) {
            if(bestScore<s.add+secondHalf[ubb].add) {
                bestScore=s.add+secondHalf[ubb].add;
                bestLIndex=i;
                bestRIndex=ubb;
            }
        }
    }
    if(bestLIndex==-1) {
        cout << "Impossible" << endl;
        return 0;
    }
    for(int i = 0; i < n/2; i++) {
        if(bestLIndex%3==0) {
            cout << "MW" << endl;
        } else if(bestLIndex%3==1) {
            cout << "LW" << endl;
        } else {
            cout << "LM" << endl;
        }
        bestLIndex/=3;
    }

    for(int i = n/2; i < n; i++) {
        if(secondHalf[bestRIndex].index%3==0) {
            cout << "MW" << endl;
        } else if(secondHalf[bestRIndex].index%3==1) {
            cout << "LW" << endl;
        } else {
            cout << "LM" << endl;
        }
        secondHalf[bestRIndex].index/=3;
    }
}