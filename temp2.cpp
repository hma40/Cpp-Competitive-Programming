#include<bits/stdc++.h>
 
using namespace std;
 
const int MOD = 998244353;
 
int add(int x, int y)
{
 	x += y;
 	while(x >= MOD) x -= MOD;
 	while(x < 0) x += MOD;
 	return x;
}
 
int mul(int x, int y)
{
 	return (x * 1ll * y) % MOD;
}
 
int main()
{
 	int n, x, m;
 	cin >> n >> x >> m;
 	vector<int> fib = {0, 1};
 	for(int i = 2; i <= 30; i++)
 		fib.push_back(fib[i - 1] + fib[i - 2]);
 
 
 	int max_sum = fib[x] * n;
 	vector<vector<int>> dp(max_sum + 1, vector<int>(n + 1));
 	dp[0][0] = 1;
    int operations = 0;
 	for(int i = 1; i <= x; i++){
        cout << i << endl;
 		for(int j = 0; j < max_sum; j++)
 			for(int k = 0; k < n; k++)
 			{
                operations++;
 			 	if(j + fib[i] <= max_sum)
 			 		dp[j + fib[i]][k + 1] = add(dp[j + fib[i]][k + 1], dp[j][k]);
 			}
    }
    cout << operations << endl;
	vector<int> cost(max_sum + 1, 1e9);
	cost[0] = 0;
	for(int j = 1; j <= max_sum; j++)
		for(int i = 1; i <= 30; i++)
			if(j >= fib[i])
				cost[j] = min(cost[j], cost[j - fib[i]] + 1);
 
	int ans = 0;
	for(int i = 0; i <= max_sum; i++)
		if(cost[i] == m)
			ans = add(ans, dp[i][n]);
	cout << ans << endl;
}