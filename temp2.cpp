#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#ifdef UwU
#include "C:\genshin_impact\keqing.cpp"
#else
#define debug(...) 0
#endif
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll INFLL = 1e18;
 
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define pb push_back
#define FOR(i,a,b) for(int i = (a); i < (b); ++i)
#define FORE(i,a,b) for(int i = (a); i <= (b); ++i)
#define ROF(i,a,b) for(int i = (a); i >= (b); --i)
#define trav(a,x) for(auto& a: x)
#define sz(x) (int)x.size()
#define make_unique(v) sort(all(v)); v.erase(unique(all(v)), v.end())

template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template<class T> bool ckmin(T& a, const T& b){return b<a?a=b,1:0;}
template<class T> bool ckmax(T& a, const T& b){return a<b?a=b,1:0;}
template<int D, typename T>struct vt : public vector<vt<D - 1, T>> { template<typename... Args>
	vt(int n = 0, Args... args) : vector<vt<D - 1, T>>(n, vt<D - 1, T>(args...)) {}};
template<typename T> struct vt<1, T> : public vector<T> {
	vt(int n = 0, const T& val = T()) : vector<T>(n, val) {}};
template<typename T> istream& operator>>(istream& in, vector<T>& a) {for(auto &x : a) in >> x; return in;};
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {for(auto &x : a) out << x << ' '; return out;};

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
 
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int solve2(vector<int> a, int k){
	int n = sz(a);
	FOR(i,0,n) a[i] -= i;
	int ans = k;
	map<int, vector<int>> mp;
	// create tests where there are a lot of groups
	FOR(i,0,n) mp[a[i]].pb(i);
	trav(p, mp){
		auto v = p.S;
		ordered_set<int> oset;
		trav(j, v) oset.insert(j);
		trav(i, v){
			int cur = oset.order_of_key(i);
			int next = oset.order_of_key(i+k);
			ckmin(ans, k - (next - cur));
		}
	}
	return ans;
}

void solve() {
	int n, k, q; cin >> n >> k >> q;
	vector<int> a(n); cin >> a;
	while(q--){
		ll l, r; cin >> l >> r;
		--l; --r;
		ll ans = 0;
		vector<int> arr;
		FORE(i,l,r){
			arr.pb(a[i]);
			if(sz(arr) >= k) ans += solve2(arr, k);
		}
		cout << ans << "\n";
	}
}

signed main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t = 1;
	cin >> t;
	for(int test = 1; test <= t; test++){
		solve();
	}
}

/*   /\_/\
*   (= ._.)
*   / >  \>
*/