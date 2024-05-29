#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> primes0, primes1, result1, result0;
ll k;
bool keepGoing(ll first, ll second, ll max) {
    if(log10(first)+log10(second)>18) return true;
    if(first*second>max) return true;
    return false;
}
bool possible(ll max) {
    ll count = 0;
    ll rIndex = result1.size()-1;
    //cout << max << endl;
    for(ll &x: result0) {
        if(x>max) return false;
        while(rIndex>=0&&result1[rIndex]>max/x) {
            rIndex--;
        }
        count+=rIndex+1;
        if(count>=k) {
            //cout << count << " " << lIndex << " " << result0.size() << endl;
            return true;
        }
    }
    return false;
}
void generateAll0(int maxIndex, ll startingFactor) {
    if(maxIndex<0) {
        result0.push_back(1);
        return;
    }
    if(maxIndex==0) {
        while(startingFactor<1e18) {
            result0.push_back(startingFactor);
            if(log10(startingFactor)+log10(primes0[0])>18) {
                return;
            }
            startingFactor*=primes0[0];
        }
    } else {
        while(startingFactor<1e18) {
            generateAll0(maxIndex-1, startingFactor);
            if(log10(startingFactor)+log10(primes0[maxIndex])>18) {
                return;
            }
            startingFactor*=primes0[maxIndex];
        }
    }
}
void generateAll1(int maxIndex, ll startingFactor) {
    if(maxIndex<0) {
        result1.push_back(1);
        return;
    }
    if(maxIndex==0) {
        while(startingFactor<1e18) {
            result1.push_back(startingFactor);
            if(log10(startingFactor)+log10(primes1[0])>18) {
                return;
            }
            startingFactor*=primes1[0];
        }
    } else {
        while(startingFactor<1e18) {
            generateAll1(maxIndex-1, startingFactor);
            if(log10(startingFactor)+log10(primes1[maxIndex])>18) {
                return;
            }
            startingFactor*=primes1[maxIndex];
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //result0.reserve(750000);
    //result1.reserve(750000);
    int n;
    cin >> n;
    vector<ll> prim(n);
    for(int i = 0; i < n; i++) {
        cin >> prim[i];
    }
    if(prim[0]==2) {
        int cutoff = n/3;
        for(int i = 0; i < cutoff; i++) {
            primes0.push_back(prim[i]);
        }
        for(int i = cutoff; i < n; i++) {
            primes1.push_back(prim[i]);
        }
    } else {
        for(int i = 0; i < prim.size(); i++) {
            if(i%2) primes0.push_back(prim[i]);
            else primes1.push_back(prim[i]);
        }
    }
    cin >> k;
    //cout << "got here" << endl;
    generateAll0(primes0.size()-1, 1);
    generateAll1(primes1.size()-1, 1);
    sort(begin(result0), end(result0));
    sort(begin(result1), end(result1));
    //cout << result0.size() << " " << result1.size() << endl;
    //cout << result0[0] << " " << result0.back() << " " << result1[0] << " " << result1.back() << endl;
    ll lo = 1;
    ll hi = 1e18;
    while(lo+1<hi) {
        ll mid = lo+(hi-lo)/2;
        if(possible(mid)) {
            hi=mid;
        } else {
            lo=mid;
        }
    }
    //cout << lo << " " << hi << endl;
    if(possible(lo)) {
        cout << lo << endl;
    } else {
        cout << hi << endl;
    }
}