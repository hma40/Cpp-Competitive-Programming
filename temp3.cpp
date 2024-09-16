#include <bits/stdc++.h>
#include "testlib.h"
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
using namespace std;
vector<vector<vector<int>>> gen0(11);
void gen() {
    gen0[1].push_back({1});
    for(int i = 2; i < 11; i++) {
        gen0[i].push_back({i});
        for(int j = 1; j < i; j++) {
            for(auto arr: gen0[i-j]) {
                vector<int> here;
                here.push_back(j);
                for(auto y: arr) here.push_back(y);
                gen0[i].push_back(here);
            }
        }
    }
}
vector<vector<int>> gen1;
void make(vector<int> &a) {
    if(gen1[0].size()==a.size()) return;
    vector<vector<int>> temp;
    for(int i = 0; i < a[gen1[0].size()]; i++) {
        for(auto arr: gen1) {
            arr.push_back(i);
            temp.push_back(arr);
        }
    }
    swap(temp,gen1);
    make(a);
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int max_t = 10000; // Maximum number of test cases
    const int max_sum_n = 200000; // Maximum total sum of n
    gen();
    int sum_n = 0;
    vector<pair<int,vector<int>>> tests;
    for(int i = 1; i < 11; i++) {
        for(auto arr: gen0[i]) {
            gen1.clear();
            gen1.push_back({});
            make(arr);
            for(auto which: gen1) {
                sum_n+=i;
                if(sum_n>max_sum_n||tests.size()==10000) break;
                int nextInd = 0;
                vector<int> a(i);
                for(int j = 0; j < arr.size(); j++) {
                    for(int k = which[j]+1; k <= arr[j]; k++) {
                        a[nextInd++]=k;
                    }
                    for(int k = 1; k < which[j]+1; k++) {
                        a[nextInd++]=k;
                    }
                }
                tests.push_back({i, a});
            }
            if(sum_n>max_sum_n||tests.size()==10000) break;
        }
        if(sum_n>max_sum_n||tests.size()==10000) break;
    }
    cout << tests.size() << endl;
    return 0;
}
