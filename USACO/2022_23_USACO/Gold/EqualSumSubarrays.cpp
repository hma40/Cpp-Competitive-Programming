#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Subarray {
    int start,end;
    long long sum;
    Subarray(int start, int end, long long sum): start(start), end(end), sum(sum) {
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<long long> numbers(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    vector<Subarray> subarrays;
    for (int i = 0; i < n; i++) {
        long long sumHere = 0;
        for (int j = i; j < n; j++) {
            sumHere += numbers[j];
            subarrays.push_back(Subarray(i,j,sumHere));
        }
    }
    sort(begin(subarrays), end(subarrays), [](const Subarray a, const Subarray b) -> bool{
        return a.sum<b.sum;
    });
    vector<long long> answer(n, 1000000000000000000LL);
    
    for (int i = 0; i < n; i++) {
        vector<long long> included;
        vector<long long> notIncluded;
        for(Subarray &s: subarrays) {
            if(s.start<=i&&s.end>=i) {
                included.push_back(s.sum);
            } else {
                notIncluded.push_back(s.sum);
            }
        }
        int iPointer = 0, niPointer = 0;
        
        if (notIncluded.size() == 1) {
            answer[i] = min(abs(included[0] - notIncluded[0]), abs(included[1] - notIncluded[0]));
            continue;
        }
        if (included.back() < notIncluded[0]) {
            answer[i] = notIncluded[0] - included.back();
        } else if (notIncluded.back() < included[0]) {
            answer[i] = included[0] - notIncluded.back();
        } else if (notIncluded.back() < included.back()) {
            while (notIncluded[niPointer] < included[0]) {
                niPointer++;
            }
            if (niPointer > 0) {
                niPointer--;
            }
            answer[i] = abs(included[0] - notIncluded[niPointer]);
            for (; niPointer < notIncluded.size(); niPointer++) {
                while (included[iPointer] < notIncluded[niPointer]) {
                    iPointer++;
                }
                if (iPointer > 0) {
                    iPointer--;
                }
                answer[i] = min(answer[i], min(abs(included[iPointer] - notIncluded[niPointer]), abs(included[iPointer + 1] - notIncluded[niPointer])));
            }
        } else {
            while (included[iPointer] < notIncluded[0]) {
                iPointer++;
            }
            if (iPointer > 0) {
                iPointer--;
            }
            answer[i] = abs(notIncluded[0] - included[iPointer]);
            for (; iPointer < included.size(); iPointer++) {
                while (notIncluded[niPointer] < included[iPointer]) {
                    niPointer++;
                }
                if (niPointer > 0) {
                    niPointer--;
                }
                answer[i] = min(answer[i], min(abs(included[iPointer] - notIncluded[niPointer]), abs(included[iPointer] - notIncluded[niPointer + 1])));
            }
        }
    }

    for (long long ans : answer) {
        cout << ans << "\n";
    }

    return 0;
}