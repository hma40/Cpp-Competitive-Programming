#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pi = pair<int, int>;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
ll mod = 1000000007;
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
vector<ld> noDates, oneDate;
ld getChance(int a, int b) {
    if(a==0) return oneDate[b];
    return (oneDate[b]-noDates[b]*oneDate[a-1]/noDates[a-1])/noDates[a-1]; 
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("cowdate.in", "r", stdin);
    freopen("cowdate.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays
    int n;
    cin >> n;
    vector<ld> prob(n);
    F0R(i, n) {
        cin >> prob[i];
        prob[i]/=1e6;
    }
    noDates.resize(n);
    oneDate.resize(n);
    noDates[0]=1-prob[0];
    oneDate[0]=prob[0];
    for(int i = 1; i < n; i++) {
        noDates[i]=noDates[i-1]*(1-prob[i]);
        oneDate[i]=oneDate[i-1]*(1-prob[i])+noDates[i-1]*prob[i];
    }
    ld ans = prob[n-1];
    for(int i = 0; i < n-1; i++) {
        int left = i+1;
        int right = n-1;
        while(left+2<right) {
            int midL = (2*left+right)/3;
            int midR = (left+2*right)/3;
            if(getChance(i,midL)>getChance(i,midR)) {
                right=midR;
            } else {
                left=midL;
            }
        }
        for(int j = left; j <= right; j++) {
            ans=std::max(ans, getChance(i,j));
        }
    }
    ans*=1e6;
    int a = (int)ans;
    int b = a+1;
    if(abs(b-ans)<0.000001) {
        cout << b << endl;
    } else {
        cout << a << endl;
    }
    return 0;
}