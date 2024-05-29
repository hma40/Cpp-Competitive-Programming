#include <iostream>
#include <vector>
using namespace std;
int gcd(int a, int b) {
    if(a%b==0) {
        return b;
    }
    return gcd(b, a%b);
}

int main() {
    long long n;
    cin >> n;
    vector<long long> coprime;
    for(int i = 1; i <n; i++) {
        if(gcd(n, i)==1) {
            coprime.push_back(i);
        }
    }
    long long prod = 1;
    for(int i = 0; i < coprime.size(); i++) {
        prod*=coprime[i];
        prod%=n;
    }
    string ans="";
    if(prod==1) {
        cout << coprime.size() << endl;
        for(int i = 0; i < coprime.size(); i++) {
            ans+=to_string(coprime[i]);
            ans+=" ";
        }
        cout << ans.substr(0,ans.length()-1);
    } else {
        cout << coprime.size()-1 << endl;
        for(int i = 0; i < coprime.size(); i++) {
            if(prod==coprime[i]) {
                continue;
            } else {
                ans+=to_string(coprime[i]);
                ans+=" ";
            }
        }
        cout << ans.substr(0,ans.length()-1);
    }
}