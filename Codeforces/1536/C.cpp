#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>

using namespace std;
int gcd(int a, int b) {
    if(a%b==0) return b;
    return gcd(b, a%b);
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    for(; t > 0; t--) {
        int n;
        string s;
        cin >> n >> s;
        map<pair<int, int>, int> mp;
        int numD=0, numK=0;
        string ans="";
        for(int i = 0; i < s.length(); i++) {

            if(s[i]=='D') {
                numD++;
            } else {
                numK++;
            }
            pair<int, int> temp;
            if(numD==0) {
                temp.first=0;
                temp.second=1;
            } else if(numK==0) {
                temp.first=1;
                temp.second=0;
            } else {
                int newD = numD;
                int newK = numK;
                newD/=gcd(numD, numK);
                newK/=gcd(numD, numK);
                temp.first=newD;
                temp.second=newK;
            }
            //cout << numD << " " << numK << endl;
            //cout << temp.first << " " << temp.second << " " <<mp.count(temp) << endl << endl;
            mp[temp]++;
            ans += to_string(mp[temp]) + " ";
            //cout << endl;
        }
        cout << ans << endl;    
    }
}