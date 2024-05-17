/*
SOLUTION
We note that any sequence of N colors, with at least K of the same color at some point in the sequence, is a valid coloring
Proof: lets say the sequence of same coloring goes from index i...i+K-1. Then, paint tiles 1 through k with the color of tile 1, then
    tiles 2 through k+1 with color of tile 2, etc. until i-1 through i+K-2 with color of tile i-1. Then, do the same thing from the back.
    Paint N-k+1 through N with the color of N, etc. Paint i through i+K-1 last, and that is our final result
We maintain two dynamic programming arrays: one for valid sequences, and one for invalid sequences. A valid sequence can be generated from
    an already valid sequence of length 1 less, concatenated with any color, or an invalid sequence concatenated with k of the same sequence. 
    However, in the second case we note that to avoid overcount the color cannot be the same as the last color of the invalid sequence.
Similarly, for invalid sequences, an invalid sequence of length i can be generated with an invalid sequence of length i-1, i-2, ..., 
    i-k+1, and then concatenating a sequence of the same color 1, 2, ..., k-1 times. To avoid overcount, the color cannot be the same
    as the last color of the invalid sequence. 
This solution looks like it would take O(NK) time which is too slow, but we can keep a running sum/sliding window of the sum of the last k
    invalid sequences, and doing so makes our solution O(N). 
*/

#include <iostream>
using namespace std;
using ll = long long;
ll mod = 1000000007;
void add(ll &toBeChanged, ll toBeAdded) {
    toBeChanged+=toBeAdded;
    //prevent negative results from modulus operations
    toBeChanged+=mod;
    toBeChanged%=mod;
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);
    ll n,m,k;
    cin >> n >> m >> k;
    ll validSequences[n+1]={0};
    ll invalidSequences[n+1]={0};
    //base cases: m ways to create an invalid sequence of length 1
    ll runningSum = m; 
    invalidSequences[1]=m;
    for(int i = 2; i <= n; i++) {
        if(i==k) {
            //base case for validSequences: m ways to create a k-size valid sequence
            add(validSequences[i], m);
        } else if(i>k) {
            //recursive case for validSequences
            add(validSequences[i], validSequences[i-1]*m);
            add(validSequences[i], (m-1)*invalidSequences[i-k]);
        }
        if(i>=k) {
            //If i>=k, then we have to subtract the invalidSequences[i-k+1] from running sum, as they will produce valid sequences.
            add(invalidSequences[i], (m-1)*runningSum);
            add(runningSum, invalidSequences[i]);
            add(runningSum, -invalidSequences[i-k+1]);
        } else {
            //When i<k, the number of invalid sequences of size i is just m times the number of invalid sequences of size i-1
            add(invalidSequences[i], invalidSequences[i-1]*m);
            add(runningSum, invalidSequences[i]);
        }
    }
    cout << validSequences[n] << endl;
}