#include <iostream>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    string ans = "";
    for(;t>0;t--) {
        int n;
        cin >> n;
        int towers[n];
        for(int i = 0; i < n; i++) {
            cin >> towers[i];
        }
        int minSkipFriend[n+1], minSkipYou[n+1];
        for(int i = 0; i <= n; i++) {
            minSkipFriend[i]=-1;
            minSkipYou[i]=-1;
        }
        minSkipFriend[0]=0;
        for(int i = 0; i < n-1; i++) {
            if(minSkipFriend[i]!=-1) {
                int temp, temp2;
                temp = minSkipFriend[i] + towers[i];
                temp2 = temp + towers[i+1];
                if(minSkipYou[i+1]==-1) {
                    minSkipYou[i+1] = temp;
                } else {
                    minSkipYou[i+1] = min(minSkipYou[i+1], temp);
                }
                if(minSkipYou[i+2]==-1) {
                    minSkipYou[i+2]=temp2;
                } else {
                    minSkipYou[i+2]=min(temp2, minSkipYou[i+2]);
                }
            }
            if(minSkipYou[i]!=-1) {
                if(minSkipFriend[i+1]==-1) {
                    minSkipFriend[i+1]=minSkipYou[i];
                } else {
                    minSkipFriend[i+1]=min(minSkipFriend[i+1], minSkipYou[i]);
                }
                if(minSkipFriend[i+2]==-1) {
                    minSkipFriend[i+2]=minSkipYou[i];
                } else {
                    minSkipFriend[i+2]=min(minSkipFriend[i+2], minSkipYou[i]);
                }
            }
        }
        int answ = 0;
        if(minSkipYou[n-1]==-1) {
            answ = minSkipFriend[n-1]+towers[n-1];
        } else if(minSkipFriend[n-1]==-1) {
            answ = minSkipYou[n-1];
        } else {
            answ = min(min(minSkipYou[n-2], minSkipYou[n-1]), minSkipFriend[n-1]+towers[n-1]);
        }
        ans+=to_string(answ)+"\n";
    }
    cout << ans;
}   