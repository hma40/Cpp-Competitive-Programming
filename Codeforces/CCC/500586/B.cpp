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
void printArray(vector<pi> &v) {
    if(debug) {
        cout << '[';
        F0R(i, v.size()) cout << v[i].f << " " << v[i].s << ", ";
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
struct SegTree {
    int n;
    vector<ll> tree;
    SegTree(int nn): n(nn) {
        while(n!=(n&(-n))) {
            n++;
        }
        tree.resize(2*n);
        F0R(i, 2*n) tree[i]=2e9;
    }
    void set(int index, int value) {
        index+=n;
        tree[index]=value;
        for(index/=2; index>=1; index/=2) { 
            if(tree[index*2+1]<tree[index*2]) {
                tree[index]=tree[index*2+1];
            } else {
                tree[index]=tree[index*2];
            }
        }
    }   
    int minim(int left, int right) {
        left+=n;
        right+=n;
        int ans = 2e9;
        while(left<=right) {
            if(left%2==1) {
                if(tree[left]<ans) {
                    ans=tree[left];
                }
                left++;
            }
            if(right%2==0) {
                if(tree[right]<ans) {
                    ans=tree[right];
                }
                right--;
            }
            left/=2;
            right/=2;
        }
        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<pi> sequences(n);
    int maxMin = 0;
    F0R(i, n) {
        cin >> sequences[i].f >> sequences[i].s;
        if(sequences[i].f>sequences[i].s) swap(sequences[i].f, sequences[i].s);
        maxMin=max(maxMin, min(sequences[i].f, sequences[i].s));
    }
    sort(begin(sequences), end(sequences), [](const pi a, const pi b)-> bool{
        return a.s<b.s;
    });
    SegTree st(n);
    F0R(i, n) {
        if(sequences[i].s<=maxMin) {
            st.set(i, sequences[i].s);
        } else {
            st.set(i, sequences[i].f);
        }
    }
    int ans = maxMin-st.minim(0, n-1);
    F0R(i, n) {
        if(sequences[i].s>maxMin) {
            int firstPart = st.minim(0, i-1);
            int secondPart = st.minim(i+1, n-1);
            ans=min(ans, sequences[i].s-min(firstPart, secondPart));
        }
        st.set(i, sequences[i].s);
    }
    cout << ans << endl;
    return 0;
}