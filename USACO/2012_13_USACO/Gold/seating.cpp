#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
void printArray(vector<vector<int>> &v) {
    if(debug) {
        cout << "{\n";
        trav(y, v) printArray(y);
        cout << "}" << endl;
    }
}
struct SegTree {
    int n;
    vector<int> maxTree, minTree, min, max, lazySet;
    SegTree(int nn): n(nn) {
        while(n!=(n&(-n))) n++;
        maxTree.resize(2*n);
        minTree.resize(2*n, 1<<30);
        lazySet.resize(2*n, -1);
        min.resize(2*n);
        max.resize(2*n);
        FOR(i, n, 2*n) {
            min[i]=max[i]=i-n;
        }
        for(int i = n-1; i > 0; i--) {
            min[i]=min[2*i];
            max[i]=max[2*i+1];
        }
    }
    vector<int> getData() {
        vector<int> data(n);
        for(int i = 0; i < n; i++) {
            data[i]=getMax(i,i,1);
        }
        return data;
    }
    int getMax(int left, int right, int index) {
        if(index>=n) {
            return maxTree[index];
        }
        if(lazySet[index]!=-1) {
            lazySet[2*index]=lazySet[2*index+1]=lazySet[index];
            maxTree[2*index]=maxTree[2*index+1]=lazySet[index];
            minTree[2*index]=minTree[2*index+1]=lazySet[index];
        }
        lazySet[index]=-1;
        if(left==min[index]&&right==max[index]) {
            return maxTree[index];
        }
        int ans = 0;
        if(min[2*index]<=right&&max[2*index]>=left) {
            ans=getMax(left, std::min(right, max[2*index]), 2*index);
        }
        if(min[2*index+1]<=right&&max[2*index+1]>=left) {
            ans=std::max(ans, getMax(std::max(left, min[2*index+1]),right, 2*index+1));
        }
        return ans;
    }
    int getMin(int left, int right, int index) {
        if(index>=n) {
            return maxTree[index];
        }
        if(lazySet[index]!=-1) {
            lazySet[2*index]=lazySet[2*index+1]=lazySet[index];
            maxTree[2*index]=maxTree[2*index+1]=lazySet[index];
            minTree[2*index]=minTree[2*index+1]=lazySet[index];
        }
        lazySet[index]=-1;
        if(left==min[index]&&right==max[index]) {
            return minTree[index];
        }
        int ans = 1<<30;
        if(min[2*index]<=right&&max[2*index]>=left) {
            ans=getMin(left, std::min(right, max[2*index]), 2*index);
        }
        if(min[2*index+1]<=right&&max[2*index+1]>=left) {
            ans=std::min(ans, getMin(std::max(left, min[2*index+1]),right, 2*index+1));
        }
        return ans;
    }
    void rangeSet(int left, int right, int value, int index) {
        if(index>=n) {
            maxTree[index]=value;
            minTree[index]=value;
            return;
        }
        if(left==min[index]&&right==max[index]) {
            lazySet[index]=value;
            maxTree[index]=value;
            minTree[index]=value;
            return;
        }
        if(lazySet[index]!=-1) {
            lazySet[2 * index] = lazySet[2 * index + 1] = lazySet[index];
            maxTree[2*index]=maxTree[2*index+1]=lazySet[index];
            minTree[2*index]=minTree[2*index+1]=lazySet[index];
            lazySet[index]=-1;
        }
        if(min[2*index]<=right&&max[2*index]>=left) {
            rangeSet(left, std::min(right, max[2*index]), value, 2*index);
        }
        if(min[2*index+1]<=right&&max[2*index+1]>=left) {
            rangeSet(std::max(left, min[2*index+1]), right, value, 2*index+1);
        }
        maxTree[index]=std::max(maxTree[2*index], maxTree[2*index+1]);
        minTree[index]=std::min(minTree[2*index], minTree[2*index+1]);
    }
};
int n,m;
int findLastNonempty2(SegTree &mst, int index) {
    int left = 0, right = index;
    if(mst.getMin(0,index,1)!=0) return -1;
    while(left+1<right) {
        int mid = (left+right)/2;
        if(mst.getMin(mid, index, 1)==0) {
            left=mid;
        } else {
            right=mid;
        }
    }

    if(mst.getMin(right,index,1)==0) return right;
    return left;
}
int findFirstNonempty2(SegTree &mst, int index) {
    int left = index, right = n-1;
    if(mst.getMin(index,n-1,1)!=0) return n;
    while(left+1<right) {
        int mid = (left+right)/2;
        if(mst.getMin(index, mid, 1)==0) {
            right=mid;
        } else {
            left=mid;
        }
    }
    if(mst.getMin(index,left,1)==0) return left;
    return right;
}
static int findFirstNonempty(SegTree &mst, int index) {
    int left = index, right = n-1;
    if(mst.getMin(index,n-1,1)!=0) return n;
    while(left+1<right) {
        int mid = (left+right)/2;
        if(mst.getMin(index, mid, 1)!=0) {
            left=mid;
        } else {
            right=mid;
        }
    }
    if(mst.getMin(index,left,1)==0) return left;
    return right;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    //debug=false; //ENABLE before submitting code to disable printArrays

    cin >> n >> m;
    SegTree mst(n);
    mst.rangeSet(0, n-1, n, 1);
    int ans = 0;
    for(int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if(c=='A') {
            int partySize;
            cin >> partySize;
            if(mst.getMax(0, n-1,1)<partySize) {
                ans++;
                continue;
            }
            int l = 0, r = n-1;
            while(l+1<r) {
                int mid = (l+r)/2;
                if(mst.getMax(0,mid,1)>=partySize) {
                    r=mid;
                } else {
                    l=mid;
                }
            }
            if(mst.getMax(0,l,1)>=partySize) {
                r=l;
            }
            mst.rangeSet(r, r+partySize-1, 0, 1);
            int firstEmpty = r+partySize;
            if(firstEmpty<n) {
                int fn = findFirstNonempty2(mst, firstEmpty);
                int numEmpty = fn-firstEmpty;
                if(numEmpty>0) {
                    mst.rangeSet(firstEmpty, fn - 1, numEmpty, 1);
                }
            }
        } else {
            int lBound, rBound;
            cin >> lBound >> rBound;
            --lBound;
            --rBound;
            int firstfirst = lBound, lastlast=rBound;
            if(lBound>0) {
                firstfirst=findLastNonempty2(mst, lBound-1)+1;
            }
            if(rBound<n-1) {
                lastlast=findFirstNonempty2(mst, rBound+1)-1;
            }
            mst.rangeSet(firstfirst,lastlast,lastlast-firstfirst+1,1);
        }
    }
    cout << ans << endl;
    return 0;
}