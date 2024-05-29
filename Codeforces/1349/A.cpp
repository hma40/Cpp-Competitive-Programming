#include <unordered_set>
#include <ioStream>
#include <vector>
#include <math.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> primes;
    int total[200001] = {0};
    for(int i = 2; i <= 200000; i++) {
        vector<int> bruh(((int)log(200000)/log(i)+3));
        primes.push_back(bruh);
    }
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for(int j = 2; j * j <= k; j++) {
            total[j]++;
            int count = 0;
            while(k%j==0) {
                k/=j;
                count++;
            }
            primes[j-2][count]++;
        }
        if(k!=1) {
            total[k]++;
            primes[k-2][1]++;
        }
    }
    long long ans = 1;
    for(int i = 2; i <= 200000; i++) {
        int cnt = n-total[i];
        int j = 0;
        if(cnt<2) {
            for(; j < primes[i-2].size(); j++) {
                cnt += primes[i-2][j];
                //cout << j << " " << i << " " << primes[i-2][j] << endl;
                if(cnt>1) break;
            }
        }
        for(int k = 0; k < j; k++) {
            ans*=i;
        }
    }
    cout << ans;
}