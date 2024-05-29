#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    int arr[n];
    vector<int> min(512, 1000);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    min[0]=0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 512; j++) {
            int m = min[arr[i]^j];
            if(m<arr[i]) {
                min[j]=std::min(min[j], arr[i]);
            }
        }
    }
    int count = 0;
    string ans = "";
    for(int i = 0; i < 512; i++) {
        if(min[i]!=1000) {
            //cout << "i: " << i << " min: " << min[i] << endl;
            count++;
            if(ans=="") {
                ans+=to_string(i);
            } else {
                ans+=" "+to_string(i);
            }
        }
    }
    cout << count << endl << ans << endl;
}