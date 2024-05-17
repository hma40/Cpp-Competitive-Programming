#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
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
vector<__int128> powp(1000005);
const __int128 MUL = 1000000007;
const __int128 MOD = (1LL<<61)-1;
struct HashStr {
    vector<__int128> hashArray;
    HashStr() {}
    HashStr(string s) {
        hashArray.resize(s.size()+1);
        F0R(i, s.size()) {
            hashArray[i+1]=hashArray[i]*MUL%MOD+s[i];
        }
    }
    ll getHash(int l, int r) {
        __int128 RAW = hashArray[r+1]-hashArray[l]*powp[r-l+1];
        RAW%=MOD;
        RAW+=MOD;
        RAW%=MOD;
        return RAW;
    }
};
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays
    int n,m;
    cin >> n >> m;
    powp[0]=1;
    FOR(i, 1, 1000005) {
        powp[i]=powp[i-1]*MUL%MOD;
    }
    vector<HashStr> hashes(2*n);
    F0R(i, 2*n) {
        string temp;
        cin >> temp;
        hashes[i]=HashStr(temp);
    }
    FOR(len, 1, m) {
        F0R(left, m-len) {
            set<ll> spottyHash;
            F0R(i, n) {
                spottyHash.insert(hashes[i].getHash(left,left+len-1));
            }
            bool fail = false;
            FOR(i, n, 2*n) {
                ll temp = hashes[i].getHash(left, left+len-1);
                if(spottyHash.count(temp)) {
                    fail=true;
                }
            }
            if(!fail) {
                cout << len << endl;
                return 0;
            }
        }
    }
    return 0;
}