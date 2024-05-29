#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    string s;
    int q;
    cin >> s >> q;
    int n = s.size();
    vector<vector<bool>> isPalindrome(n, vector<bool>(n));
    for(int i = 0; i < n; i++) {
        isPalindrome[i][i]=true;
    }
    for(int i = 0; i < n-1; i++) {
        if(s[i]==s[i+1]) isPalindrome[i][i+1]=true;
    }
    for(int i = 2; i < n; i++) {
        for(int j = i-2; j >= 0; j--){
            isPalindrome[j][i]=isPalindrome[j+1][i-1]&&s[i]==s[j];
        }
    }
    vector<vector<int>> palindromeCount(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        palindromeCount[i][i]=1;
    }
    for(int i = 0; i < n-1; i++) {
        if(isPalindrome[i][i+1]) {
            palindromeCount[i][i+1]=3;
        } else {
            palindromeCount[i][i+1]=2;
        }
    }
    for(int i = 2; i < n; i++) {
        for(int j = i-2; j >= 0; j--) {
            if(isPalindrome[j][i]) {
                palindromeCount[j][i]=1;
            }
            palindromeCount[j][i]+=palindromeCount[j+1][i]+palindromeCount[j][i-1]-palindromeCount[j+1][i-1];
        }
    }
    string ans = "";
    for(;q>0;q--) {
        int x,y;
        cin >> x >> y;
        ans+=to_string(palindromeCount[x-1][y-1])+"\n";
    }
    cout << ans;
}