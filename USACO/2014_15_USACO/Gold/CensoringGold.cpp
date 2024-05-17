#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
string tostr(__int128 bruh) {
    if(bruh==0) return "0";
    string ret;
    while(bruh) {
        ret+=to_string((int)(bruh%10));
        bruh/=10;
    }
    reverse(begin(ret), end(ret));
    return ret;
}
struct Hash {
    __int128 mod = (1LL<<61)-1;
    __int128 x = 1000000007;
    vector<__int128> hashArray;
    vector<__int128> powX;
    Hash(): hashArray(1,(__int128)0){
        powX.resize(110000);
        powX[0]=1;
        FOR(i, 1, 110000) {
            powX[i]=powX[i-1]*x%mod;
        }
    }
    void add(int pos, char letter) {
        __int128 value = (hashArray[pos-1]*x+letter)%mod;
        if(pos==hashArray.size()) {
            hashArray.add(value);
        } else {
            hashArray[pos]=value;
        }
    }
    ll getHash(int left, int right) {
        __int128_t raw = hashArray[right+1]-hashArray[left]*powX[right-left+1];
/*         cout << "RAW: " << tostr(raw) << endl;
        cout << "LL: " << (ll)raw << endl; */
        raw%=mod;
        raw+=mod;
        raw%=mod;
        return (ll)raw;
    }
    Hash(string s): hashArray(1,(__int128)0){
        powX.resize(110000);
        powX[0]=1;
        FOR(i, 1, 110000) {
            powX[i]=powX[i-1]*x%mod;
        }
        F0R(i, s.size()) add(i+1, s[i]);
    }
};

void printArray(vector<__int128> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << tostr(v[i]) << ", ";
        cout << ']' << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout); 
    //debug=false; //ENABLE before submitting code to disable printArrays
    map<int, set<ll>> avoid;
    string s, result;
    int n;
    cin >> s >> n;
    while(n--) {
        string temp;
        cin >> temp;
        Hash tmp(temp);
        //printArray(tmp.hashArray);
        avoid[temp.size()].insert(tmp.getHash(0,temp.size()-1));
    }
    Hash res;
/*     trav(pr, avoid) {
        cout << pr.f << endl;
        trav(bruh, pr.s) cout << bruh << " ";
        cout << endl;
    } */
    //cout << th << endl;
    F0R(i, s.size()) {
        //cout << i << endl;
        result+=s[i];
        res.add(result.size(), s[i]);
        while(true) {
            bool didAnything = false;
            trav(pr, avoid) {
                if(result.size()>=pr.first) {
                    ll hsh = res.getHash(result.size()-pr.first,result.size()-1);
                    if(pr.second.count(hsh)) {
                        didAnything=true;
                        F0R(x, pr.first) result.pop_back();
                    }
                } 
            }
            if(!didAnything) break;
        }
    }
    cout << result << endl;
    return 0;
}