#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int numChars = 20;
unordered_map<char, int> charToInt;
bool badChars(char c) {
    return c=='m'||c=='i'||c=='l'||c=='d'||c=='r'||c=='e';
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    string s;
    cin >> s;
    int index = 0;
    for(int i = 0; i < 26; i++) {
        char c = (char)('a'+i);
        if(badChars(c)) continue;
        charToInt[c]=index;
        index++;
    }
    for(char c: s) {
        if(badChars(c)) {
            numChars=8;
            charToInt.clear();
            charToInt['m']=0;
            charToInt['i']=1;
            charToInt['l']=2;
            charToInt['d']=3;
            charToInt['r']=4;
            charToInt['e']=5;
            charToInt['b']=6;
            charToInt['s']=7;
        }
    }
    vector<vector<int>> consec(numChars, vector<int>(numChars));
    for(int i = 1; i < s.size(); i++) {
        consec[charToInt[s[i-1]]][charToInt[s[i]]]++;
    }
    vector<int> leastTimes(1<<numChars, 1<<30);
    leastTimes[0]=1;
    for(int i = 1; i < 1<<numChars; i++) {
        vector<int> here;
        for(int j = 0; j < numChars; j++) {
            if((i&(1<<j))!=0) {
                here.push_back(j);
            }
        }
        for(int j: here) {
            int total = leastTimes[i^(1<<j)];
            for(int k: here) {
                total+=consec[j][k];
            }
            leastTimes[i]=min(total, leastTimes[i]);
        }
    }
    cout << leastTimes[(1<<numChars)-1] << endl;
}