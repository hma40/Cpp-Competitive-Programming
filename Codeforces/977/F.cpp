#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++) cin >> arr[i]; 
    map<int, int> maxConseq;
    maxConseq[arr[0]]=1;
    for(int i = 1; i < n; i++) {
        maxConseq[arr[i]]=max(maxConseq[arr[i]-1]+1, maxConseq[arr[i]]);
    }
    string ans = "";
    int maxmax=0;
    int first, last;
    for(pair<int, int> p: maxConseq) {
        if(p.second>maxmax) {
            maxmax=p.second;
            last=p.first;
            first=p.first-p.second+1;
        }
    }
    bool needSpace=false;
    ans+=to_string(maxmax)+"\n";
    for(int i = 0; i < n; i++) {
        if(arr[i]==first) {
            first++;
            if(!needSpace) {
                needSpace=true;
                ans+=to_string(1+i);
            } else {
                ans+=" "+to_string(1+i);
            }
        }
    }
    cout << ans << endl;
}