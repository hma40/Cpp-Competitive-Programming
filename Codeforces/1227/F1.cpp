#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 998244353;
bool debug = true;
vector<string> split(string s, char delimiter) {
    vector<string> ret;
    ret.push_back("");
    F0R(i, s.length()) {
        if(s[i]==delimiter) {
            ret.add("");
        } else {
            ret.back()+=s[i];
        }
    }
    return ret;
}
struct Compare {
    bool operator()(pair<int, ll> a, pair<int, ll> b) {
        return a.second>b.second;
    }
};
void printArray(vector<int> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<ll> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<string> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i] << ", ";
        cout << ']' << endl;
    }
}
void printArray(vector<vector<int>> &v) {
    if(debug) {
        cout << "{\n";
        trav(y, v) printArray(y);
        cout << "}" << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    ll n,k;
    cin >> n >> k;
    vector<int> answers(n);
    F0R(i, n) cin >> answers[i];
    vector<vector<int>> ways(n, vector<int> (4005));
    //ways[a][b]: first a answers, b-2000 more right answers than wrong answers
    if(n==1||k==1) {
        cout << 0 << endl;
        return 0;
    }
    if(answers[0]==answers[1]) {
        ways[0][2001]=k;
    } else {
        ways[0][2001]=k-2;
        ways[0][2000]=1;
        ways[0][2002]=1;
    }
    FOR(letter, 1, n-1) {
        FOR(change, 1, 4003) {
            int actualChange = change-2001;
            if(answers[letter]==answers[letter+1]) {
                ways[letter][change]+=ways[letter-1][change]*k%mod;
                ways[letter][change]%=mod;
            } else {
                ways[letter][change]+=ways[letter-1][change]*(k-2)%mod;
                ways[letter][change]%=mod;
                ways[letter][change]+=ways[letter-1][change-1];
                ways[letter][change]%=mod;
                ways[letter][change]+=ways[letter-1][change+1];
                ways[letter][change]%=mod;
            }
        }
    }
    FOR(change, 1, 4003) {
        int actualChange = change-2001;
        if(answers[n-1]==answers[0]) {
            ways[n-1][change]+=ways[n-1-1][change]*k%mod;
            ways[n-1][change]%=mod;
        } else {
            ways[n-1][change]+=ways[n-1-1][change]*(k-2)%mod;
            ways[n-1][change]%=mod;
            ways[n-1][change]+=ways[n-1-1][change-1];
            ways[n-1][change]%=mod;
            ways[n-1][change]+=ways[n-1-1][change+1];
            ways[n-1][change]%=mod;
        }
    }
    ll ans = 0;
    FOR(i, 2002, 4004) {
        ans+=ways[n-1][i];
        ans%=mod;
    }
    cout << ans << endl;
    return 0;
}