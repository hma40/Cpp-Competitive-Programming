#include <bits/stdc++.h>

#define int __int128_t

using namespace std;
int gcd(int a, int b) {
    if(a<0) a*=-1;
    if(b<0) b*=-1;
    if(b==0) return a;
    return gcd(b, a%b);
}
struct Frac {
    int n, d;
    Frac(int n, int d) {
        this->n=n;
        this->d=d;
    }
};


Frac add(Frac a, Frac b) {
    int g = a.d*b.d/gcd(a.d,b.d);
    int num = a.n*(g/a.d)+b.n*(g/b.d);
    int gg=gcd(num, g);
    num/=gg;
    g/=gg;
    return Frac(num, g);
}
Frac div(Frac a, int x) {
    int g = gcd(x, a.n);
    a.n/=g;
    a.d*=(x/g);
    return a;
}
// std::ostream& operator<<(std::ostream& os, const Frac f) {
//         os << f.n << "/" << f.d;
//     return os;
// }
int test(int num, int times) {
    // cout << num << " " << times << "LINE 35 " << endl;
    for(int i = 0; i < times; i++) {
        if(num%2==0) {
            num/=2;
        } else {
            num*=3;
            num++;
        }
    }
    // cout << "RETURNING " << num << endl;
    return num;
}

signed main() {
    string s; cin >> s;
    int n = s.size();
    pair<Frac,Frac> pr = {Frac(1,1), Frac(0,1)};
    for(int i = n-1; i >= 0; i--) {
        if(s[i]=='O') {
            pr.second=add(pr.second, Frac(-1, 1));
            pr.first=div(pr.first, 3);
            pr.second=div(pr.second, 3);
        } else {
            pr.first.n*=2;
            pr.second.n*=2;
        }
    }
    // cout << pr.first << " " << pr.second << endl;
    for(int i = 1; i <= (1LL<<61); i*=2) {
        Frac fra = Frac(pr.first.n*i, pr.first.d);
        fra=add(fra, pr.second);
        // cout << i << " " << fra << endl;
        int g = gcd(fra.d, fra.n);
        if(g==fra.d) {
            // cout << "GOT HERE " << fra << endl;
            int ans = fra.n/fra.d;
            if(test(ans, s.size())==(i)&&ans<=(1LL<<48)) {
                cout << (long long)ans << endl;
                return 0;
            }
        }
    }
    cout << "INVALID" << endl;
}
/*
3x+1=n
3x=n-1
x=n/3-1/3

x/2=n/3-1/3
x=2n/3-2/3

128/9-20/9=108/9=12
*/