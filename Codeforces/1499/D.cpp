#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
vector<int> countingIsHard(20000001, 0);
ll gcd(ll a, ll b) {
    if(a%b==0) return b;
    return gcd(b,a%b);
}
int main() {
    for(int i = 2; i <= 20000000; i++) {
        if(countingIsHard[i]!=0) continue;
        for(int j = i; j <= 20000000; j+=i) {
            countingIsHard[j]++;
        }
    }
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    string anss = "";
    for(;t>0;t--) {
        ll a,b,c;
        cin >> a >> b >> c;
        ll gcdd;
        if(a>b) {
            gcdd = gcd(a,b);
        } else {
            gcdd = gcd(b,a);
        }
        if(c%gcdd!=0) {
            anss += "0\n";
            continue;
        }
        c/=gcdd;
        a/=gcdd;
        b/=gcdd;
        long long ans = 0;
        for(int i = 1; i * i <= c; i++) {
            if(c%i!=0) continue;
            //cout << c << " " << i << " " << a << " " << b << endl;
            ll bruh = 0;
            ll gcddd;
            if((i+b)%a==0) {
                ans+=1 << countingIsHard[(i+b)/a];
            }
            if(i*i==c) continue;
            if((c/i+b)%a==0) {
                ans+=1 << countingIsHard[(c/i+b)/a];
            }
        }
        anss+=to_string(ans)+"\n";
    }
    cout << anss;
}