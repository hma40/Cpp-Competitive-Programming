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
    signed main() {
        ios_base::sync_with_stdio(false); 
        cin.tie(0);
        int n,m,k;
        cin >> n >> m >> k;
        vt<pair<int, int>> v(m);
        int ans = 0;
        F0R(i, m) cin >> v[i].f >> v[i].s;
        vt<vt<int>> hats(m);
        F0R(i, n) {
            int t,s;
            cin >> t >> s;
            hats[t-1].add(s);
            ans+=s;
        }
        F0R(i, m) sort(begin(hats[i]), end(hats[i]));
        map<int, int> pm;
        F0R(i, m) {
            int timesAdded = 0;
            while(hats[i].size()) {
                int freebies = (v[i].s-hats[i].back()-timesAdded*v[i].f)/v[i].f;
                timesAdded+=freebies;
                pm[hats[i].size()*v[i].f]+=freebies;
                int next = 0;
                while(hats[i].size()&&v[i].s-hats[i].back()-timesAdded*v[i].f<=v[i].f) {
                    next+=v[i].s-hats[i].back()-timesAdded*v[i].f;
                    hats[i].pop_back();
                }
                timesAdded++;
                next+=hats[i].size()*v[i].f;
                pm[next]++;
            }
        }
        priority_queue<pair<int, int>> pq;
        trav(x, pm) pq.push(x);

        while(pq.size()) {
            auto first = pq.top();
            pq.pop();
            if(first.s>k) {
                ans+=k*first.f;
                k=0;
            } else {
                ans+=first.s*first.f;
                k-=first.s;
            }
        }
        cout << ans << endl;
        return 0;
    }