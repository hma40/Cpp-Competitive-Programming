#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int last[5];
    int n = s.length();
    //cout << n << endl;
    vector<vector<long long>> intervals;
    for(int i = 0; i < 5; i++) last[i]=-1;
    for(int i = 0; i < n; i++) {
        char c = s[i];
        if(c=='b') {
            last[0]=i;
        } else if(c=='e') {
            if(last[0]!=-1) {
                last[1]=last[0];
                last[0]=-1;
            }
            if(last[4]!=-1) {
                vector<long long> temp;
                temp.push_back(last[4]);
                temp.push_back(i);
                intervals.push_back(temp);
                last[4]=-1;
            }
        } else if(c=='s') {
            if(last[2]!=-1) {
                last[3]=last[2];
                last[2]=-1;
            }
            if(last[1]!=-1) {
                last[2]=last[1];
                last[1]=-1;
            }
        } else if(c=='i') {
            if(last[3]!=-1) {
                last[4]=last[3];
                last[3]=-1;
            }
        }
    }
    long long ans=0;
    int currentIndex=0;
    for(int i = 0; i < n; i++) {
        vector<long long> temp = intervals[currentIndex];
        if(temp[0]<i) {
            currentIndex++;
            if(currentIndex>=intervals.size()) {
                break;
            }
        }
        int lastt = currentIndex;
        for(int j = currentIndex; j < intervals.size(); j++) {
            if(j>=currentIndex+1&&intervals[j][0]<intervals[lastt][1]) {
                continue;
            } else {
                //cout << ans << endl;
                lastt=j;
                ans+=n-intervals[j][1];

            }
        }
    }
    cout << ans;
}