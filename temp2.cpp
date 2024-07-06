#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = 1000000007;
 
map<pair<long long, int>, tuple<int, long long, long long>> mem;
 
tuple<int, long long, long long> calc(long long n, int k){
	if (k < 0){
		return tuple{0, 0ll, 0ll};
	}
	if (n == 1){
		return tuple{1, 1ll, 1ll};
	}
	int bit = 63 - __builtin_clzll(n);
	long long mid = (1ll << bit);
	if (mid == n){
		mid >>= 1;
		if (mem.count({n, k})){
			return mem[{n, k}];
		}
	}
	auto [f1, s1, e1] = calc(mid, k);
	auto [f2, s2, e2] = calc(n - mid, k - 1);
 
	int sub1 = (e1 % MOD) * ((e1 + 1) % MOD) % MOD * 500000004 % MOD;
	f1 = (f1 * 1ll - sub1 + MOD) % MOD;
	int sub2 = (s2 % MOD) * ((s2 + 1) % MOD) % MOD * 500000004 % MOD;
	f2 = (f2 * 1ll - sub2 + MOD) % MOD;
 
	long long p = (e1 + s2) % MOD;
	int f_cur = (f1 * 1ll + f2 + (p * 1ll * ((p + 1) % MOD) % MOD * 500000004 % MOD)) % MOD;
	long long s_cur = s1;
	long long e_cur = e2;
	if (s1 == e1 && s1 != 0){
		s_cur = (s1 + s2);
	}
	if (s2 == e2 && s2 != 0){
		e_cur = (e1 + e2);
	}
	if ((mid << 1) == n){
		mem[{n, k}] = tuple{f_cur, s_cur, e_cur};
	}
	return tuple{f_cur, s_cur, e_cur};
};
 
void solve(){
	long long n;
	int k;
	cin >> n >> k;
	cout << get<0>(calc(n, k)) << '\n';
}
 
int main()
{
#ifdef FELIX
	auto _clock_start = chrono::high_resolution_clock::now();
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	// cout.tie(0);
    freopen("file.out", "w", stdout);
	int tests = 1;
	cin >> tests;
	for (int test = 0; test < tests; test++){
		solve();
	}
    for(auto x: mem) {
        cout << "{" << x.first.first << ", " << x.first.second << "}: " << "{" << get<0>(x.second) << ", " << get<1>(x.second) << ", " << get<2>(x.second) << "}" << endl;
    }
#ifdef FELIX
	cerr << "Executed in " << chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now()
			- _clock_start).count() << "ms." << endl;
#endif
	return 0;
}