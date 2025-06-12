#include <bits/stdc++.h>
using namespace std;

const int d = 7;
const string msg = "tralalero tralala";

#define int long long

void solve() {
    string s;
    cin >> s;
    if (s == "first") {
        int n;
        cin >> n;
        s = "";
        while (n--) {
            int i;
            cin >> i;
            i *= 8;
            i += 6;
            for (int j = 0; j < d; j++) {
                s += 'a'+(i%26);
                i /= 26;
            }
        }
        // if (s == "skibidi") return;
        cout << s << "\ntralalero\n";
    } else {
        cin >> s;
        int n = s.size() / d;
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            int pow = 1, x = 0;
            for (int j = i*d; j < (i+1)*d; j++) {
                x += (s[j]-'a') * pow;
                pow *= 26;
            }
            cout << (x-6)/8 << ' ';
        }
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    solve();
}