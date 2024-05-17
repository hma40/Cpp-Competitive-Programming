#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 1000000007;

vector<int> getDigits(long long x) {
    vector<int> ret;
    while (x > 0) {
        ret.push_back(x % 10);
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    int n;
    std::cin >> n;
    long long small, large;
    std::cin >> small >> large;
    small--;
    vector<int> digits(n);
    for (int i = 0; i < n; i++) {
        std::cin >> digits[i];
    }

    vector<int> smallDigits = getDigits(small);
    vector<int> largeDigits = getDigits(large);

    vector<vector<long long>> answers(n, vector<long long>(n));
    long long here[n][20][20][3];

    for (int left = 0; left < n; left++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 20; j++) {
                for (int k = 0; k < 20; k++) {
                    for (int l = 0; l < 3; l++) {
                        here[i][j][k][l] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < smallDigits.size(); i++) {
            if (digits[left] < smallDigits[i]) {
                here[left][i][i][0] += 2;
            } else if (digits[left] == smallDigits[i]) {
                here[left][i][i][1] += 2;
            } else {
                here[left][i][i][2] += 2;
            }
        }
        here[left][1][0][0] = 1;
        for (int right = left + 1; right < n; right++) {
            for (int j = 0; j < smallDigits.size(); j++) {
                for (int k = j; k < smallDigits.size(); k++) {
                    if (k - j > right - left) continue;
                    here[right][j][k][0] += here[right - 1][j][k][0];
                    here[right][j][k][1] += here[right - 1][j][k][1];
                    here[right][j][k][2] += here[right - 1][j][k][2];
                    if (j == k) {
                        if (digits[right] < smallDigits[j]) {
                            here[right][j][k][0] += 2LL;
                        } else if (digits[right] == smallDigits[j]) {
                            here[right][j][k][1] += 2LL;
                        } else {
                            here[right][j][k][2] += 2LL;
                        }
                    } else {
                        here[right][j][k][0] += here[right - 1][j][k - 1][0];
                        here[right][j][k][2] += here[right - 1][j][k - 1][2];
                        if (digits[right] == smallDigits[k]) {
                            here[right][j][k][1] += here[right - 1][j][k - 1][1];
                        } else if (digits[right] < smallDigits[k]) {
                            here[right][j][k][0] += here[right - 1][j][k - 1][1];
                        } else {
                            here[right][j][k][2] += here[right - 1][j][k - 1][1];
                        }
                        if (digits[right] < smallDigits[j]) {
                            here[right][j][k][0] += here[right - 1][j + 1][k][0];
                            here[right][j][k][0] += here[right - 1][j + 1][k][1];
                            here[right][j][k][0] += here[right - 1][j + 1][k][2];
                        } else if (digits[right] > smallDigits[j]) {
                            here[right][j][k][2] += here[right - 1][j + 1][k][0];
                            here[right][j][k][2] += here[right - 1][j + 1][k][1];
                            here[right][j][k][2] += here[right - 1][j + 1][k][2];
                        } else {
                            here[right][j][k][0] += here[right - 1][j + 1][k][0];
                            here[right][j][k][1] += here[right - 1][j + 1][k][1];
                            here[right][j][k][2] += here[right - 1][j + 1][k][2];
                        }
                    }
                    here[right][j][k][0] %= mod;
                    here[right][j][k][1] %= mod;
                    here[right][j][k][2] %= mod;
                }
            }
        }
        for (int right = left; right < n; right++) {
            for (int k = 1; k <= smallDigits.size(); k++) {
                answers[left][right] -= here[right][0][k - 1][0];
                answers[left][right] -= here[right][0][k - 1][1];
                if (k != smallDigits.size()) {
                    answers[left][right] -= here[right][0][k - 1][2];
                }
            }
        }
    }

    for (int left = 0; left < n; left++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 20; j++) {
                for (int k = 0; k < 20; k++) {
                    for (int l = 0; l < 3; l++) {
                        here[i][j][k][l] = 0;
                    }
                }
            }
        }
        for (int i = 0; i < largeDigits.size(); i++) {
            if (digits[left] < largeDigits[i]) {
                here[left][i][i][0] += 2;
            } else if (digits[left] == largeDigits[i]) {
                here[left][i][i][1] += 2;
            } else {
                here[left][i][i][2] += 2;
            }
        }
        here[left][1][0][0] = 1;
        for (int right = left + 1; right < n; right++) {
            for (int j = 0; j < largeDigits.size(); j++) {
                for (int k = j; k < largeDigits.size(); k++) {
                    if (k - j > right - left) continue;
                    here[right][j][k][0] += here[right - 1][j][k][0];
                    here[right][j][k][1] += here[right - 1][j][k][1];
                    here[right][j][k][2] += here[right - 1][j][k][2];
                    if (j == k) {
                        if (digits[right] < largeDigits[j]) {
                            here[right][j][k][0] += 2LL;
                        } else if (digits[right] == largeDigits[j]) {
                            here[right][j][k][1] += 2LL;
                        } else {
                            here[right][j][k][2] += 2LL;
                        }
                    } else {
                        here[right][j][k][0] += here[right - 1][j][k - 1][0];
                        here[right][j][k][2] += here[right - 1][j][k - 1][2];
                        if (digits[right] == largeDigits[k]) {
                            here[right][j][k][1] += here[right - 1][j][k - 1][1];
                        } else if (digits[right] < largeDigits[k]) {
                            here[right][j][k][0] += here[right - 1][j][k - 1][1];
                        } else {
                            here[right][j][k][2] += here[right - 1][j][k - 1][1];
                        }
                        if (digits[right] < largeDigits[j]) {
                            here[right][j][k][0] += here[right - 1][j + 1][k][0];
                            here[right][j][k][0] += here[right - 1][j + 1][k][1];
                            here[right][j][k][0] += here[right - 1][j + 1][k][2];
                        } else if (digits[right] > largeDigits[j]) {
                            here[right][j][k][2] += here[right - 1][j + 1][k][0];
                            here[right][j][k][2] += here[right - 1][j + 1][k][1];
                            here[right][j][k][2] += here[right - 1][j + 1][k][2];
                        } else {
                            here[right][j][k][0] += here[right - 1][j + 1][k][0];
                            here[right][j][k][1] += here[right - 1][j + 1][k][1];
                            here[right][j][k][2] += here[right - 1][j + 1][k][2];
                        }
                    }
                    here[right][j][k][0] %= mod;
                    here[right][j][k][1] %= mod;
                    here[right][j][k][2] %= mod;
                }
            }
        }
        for (int right = left; right < n; right++) {
            for (int k = 1; k <= largeDigits.size(); k++) {
                answers[left][right] += here[right][0][k - 1][0];
                answers[left][right] += here[right][0][k - 1][1];
                if (k != largeDigits.size()) {
                    answers[left][right] += here[right][0][k - 1][2];
                }
                answers[left][right] %= mod;
                answers[left][right] += mod;
                answers[left][right] %= mod;
            }
        }
    }

    int q;
    std::cin >> q;

    for (int i = 0; i < q; i++) {
        int left, right;
        std::cin >> left >> right;
        cout << answers[left - 1][right - 1] << "\n";
    }

    return 0;
}