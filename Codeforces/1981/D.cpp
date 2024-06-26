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
#define int long long
#define vt vector
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
int repeat;
vt<int> order;
vt<set<int>> adj;
vt<set<vt<int>>> cycles;
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int MAXN = 3e5+1;
    vt<bool> isPrime(MAXN, true);
    vt<int> primes;
    for(int i = 2; i < MAXN; i++) {
        if(isPrime[i]) {
            primes.add(i);
            for(int j = i*i; j < MAXN; j+=i) {
                isPrime[j]=false;
            }
        }
    }
    vt<int> maxEdges(primes.size()+1);
    FOR(i, 1, primes.size()) {
        if(i%2) {
            maxEdges[i]=i*(i+1)/2;
        } else {
            maxEdges[i]=i*(i+1)/2-i/2+1;
        }
    }
    vt<int> numbersUsed(1e6+1);
    int cur = 1;
    FOR(i, 1, 1e6+1) {
        if(maxEdges[cur]<i-1) {
            cur++;
        }
        numbersUsed[i]=cur;
    }
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int x = numbersUsed[n];
        // cout << x << endl;
        vt<set<int>> edges(x);
        F0R(i, x) {
            F0R(j, x) {
                if(i==j) continue;
                edges[i].insert(j);
            }
        }
        int nEd = x*(x+1)/2;
        set<pair<int, int>> oddDegree;
        if(x%2==0) {
            oddDegree.insert({x-1, 0});
            oddDegree.insert({x-1, 1});
            for(int i = 2; i < x; i+=2) {
                nEd--;
                edges[i].erase(i+1);
                edges[i+1].erase(i);
            }
        }
        // cout << nEd << endl;
        repeat = x;
        while(nEd>n-1) {
            if(repeat>0) {
                repeat--;
                nEd--;
                continue;
            }
            int del = 0;
            if(oddDegree.size()) {
                auto first = *oddDegree.rbegin();
                oddDegree.erase(first);
                del=first.s;
            }
            // cout << nEd << " " << oddDegree << " " << del << " " << edges[del] << endl;
            int y = *edges[del].begin();
            if(edges[y].size()%2) {
                oddDegree.erase({edges[y].size(),y});
            } else {
                oddDegree.insert({edges[y].size()-1, y});
            }
            edges[del].erase(y);
            edges[y].erase(del);
            if(edges[del].size()%2) {
                oddDegree.insert({edges[del].size(), del});
            }
            nEd--;
        }
        // F0R(i, x) {
        //     cout << i << " " << edges[i] << endl;
        // }
        // // cout << oddDegree << endl;
        deque<int> dq;
        if(oddDegree.size()) {
            dq.push_back((*oddDegree.begin()).s);
        } else {
            dq.push_back(0);
        }
        set<int> seen;
        vt<int> ans;
        while(dq.size()) {
            int z = dq.front();
            if(edges[z].size()) {
                int next = *(edges[z].begin());
                edges[z].erase(next);
                edges[next].erase(z);
                dq.push_front(next);
            } else {
                ans.add(z);
                if(!seen.count(z)) {
                    seen.insert(z);
                    if(repeat) {
                        repeat--;
                        ans.add(z);
                    }
                }
                dq.pop_front();
            }
        }
        assert(ans.size()==n);
        trav(z, ans) cout << primes[z] << "\n";
    }
    return 0;
}