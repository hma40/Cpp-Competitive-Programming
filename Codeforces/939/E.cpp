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
void printArray(vector<long double> &v) {
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
long double getA(long double prefSum, long double lastNum, int index) {
    long double ret = lastNum;
    ret-=(prefSum+lastNum)/(index+1);
    return ret;
}
int main() {
    cout.precision(20);
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    //freopen("file.in", "r", stdin);
    //freopen("file.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays
    int n;
    cin >> n;
    vector<long double> prefSum;
    prefSum.add(0);
    long double lastNum;
    while(n--) {
        int type;
        cin >> type;
        if(type==1) {
            cin >> lastNum;
            prefSum.add(prefSum.back()+lastNum);
        } else {
            int left = 0, right = prefSum.size()-2;
            while(left+2<right) {
                int leftThird = (2*left+right)/3;
                int rightThird = (left+2*right)/3;
                long double leftDiff = getA(prefSum[leftThird], lastNum, leftThird);
                long double rightDiff = getA(prefSum[rightThird], lastNum, rightThird);
                if(leftDiff>rightDiff) {
                    right=rightThird;
                } else {
                    left=leftThird;
                }
            }
            long double ans = lastNum-(lastNum+prefSum[left])/(left+1);
            ans=max(ans, lastNum-(lastNum+prefSum[left+1])/(left+2));
            ans=max(ans, lastNum-(lastNum+prefSum[right])/(right+1));
            vector<long double> bruh;
            cout << ans << endl;
        }
    }

    return 0;
}