#include <bits/stdc++.h>
using namespace std;

/*
 We read t test‐cases.  In each test:
   1) Read n, q.
   2) Read array a[1..n].
   3) Build prefix‐XOR:   P[i] = a[1] ^ a[2] ^ … ^ a[i].
   4) Build, for each bit b=0..29, a prefix‐sum cnt[b][i] = # of indices ≤ i
      whose b-th bit is 1.
   5) For each query (ℓ,r):
        S = P[r] ^ P[ℓ-1].
        If S==0  →  answer = 0.
        Else let k = highest 1‐bit of S.
           // check if any a[i] in [ℓ,r] has bit k = 0
           int ones_k = cnt[k][r] - cnt[k][ℓ-1];
           int length = r - ℓ + 1;
           if (ones_k < length) {
             answer = 0;
           }
           else {
             // all a[i] have bit k=1, so S_k=1
             int X = S ^ (1<<k);  // removes the leading 2^k in S
             if (X==0) {
               answer = (1<<k);
             }
             else {
               int j = 31 - __builtin_clz((unsigned)X);
               int ones_j = cnt[j][r] - cnt[j][ℓ-1];
               if (ones_j < length) {
                 answer = (1<<k);
               } else {
                 answer = (1<<k) + (1<<j);
               }
             }
           }
   6) Print all q answers on one line.
*/

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t; 
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<int> a(n+1);
        for(int i=1; i<=n; i++){
            cin >> a[i];
        }

        // 1) prefix‐XOR
        vector<int> P(n+1, 0);
        for(int i=1; i<=n; i++){
            P[i] = P[i-1] ^ a[i];
        }

        // 2) prefix‐counts of “how many 1’s at bit b up to index i”
        const int B = 30;
        // cnt[b][i] = # of a[1..i] whose b-th bit is 1
        vector< array<int,B> > cnt(n+1);
        for(int b=0; b<B; b++){
            cnt[0][b] = 0;
        }
        for(int i=1; i<=n; i++){
            for(int b=0; b<B; b++){
                cnt[i][b] = cnt[i-1][b] + ((a[i] >> b) & 1);
            }
        }

        // 3) answer all queries in O(1) each
        vector<int> ans(q);
        for(int i=0; i<q; i++){
            int L, R;
            cin >> L >> R;
            int length = R - L + 1;
            int S = P[R] ^ P[L-1];
            if(S == 0){
                ans[i] = 0;
                continue;
            }
            // find topmost 1‐bit of S
            int k = 31 - __builtin_clz((unsigned)S);
            // how many of a[L..R] have bit k = 1 ?
            int ones_k = cnt[R][k] - cnt[L-1][k];
            if(ones_k < length){
                // at least one a[i] has bit_k=0 → we can force final XOR to 0
                ans[i] = 0;
                continue;
            }
            // all a[i] in [L..R] have bit k=1, so S_k must have been 1
            int X = S ^ (1 << k);
            if(X == 0){
                // we can make all lower bits vanish, leaving exactly 2^k
                ans[i] = (1 << k);
                continue;
            }
            // X != 0, let j = topmost bit of X
            int j = 31 - __builtin_clz((unsigned)X);
            int ones_j = cnt[R][j] - cnt[L-1][j];
            if(ones_j < length){
                // some a[i] has bit j=0 → still can kill bit j → result = 2^k
                ans[i] = (1 << k);
            } else {
                // every a[i] has bit j=1 → cannot clear that bit, so result = 2^k + 2^j
                ans[i] = (1<<k) + (1<<j);
            }
        }

        // print the q answers on one line
        for(int i=0; i<q; i++){
            if(i) cout << ' ';
            cout << ans[i];
        }
        cout << "\n";
    }
    return 0;
}
