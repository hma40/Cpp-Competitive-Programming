#include <bits/stdc++.h>

#define int long long

using namespace std;
int grid[9][9]; 
bool poss(int i, int j) {
    set<int> possVal;
    for(int ia = 0; ia < 9; i++) {
        possVal.insert(ia+1);
    }
    for(int ia = 0; ia < 9; i++) {
        possVal.erase(grid[ia][i]);
        possVal.erase(grid[i][ia]);
    }
    for(int a = 0; a < 9; a++ ){
        for(int b = 0; b < 9; b++) {
            if(a/3==i&&b/3==j) {
                possVal.erase(grid[a][b]);
            }
        }
    }
    if(possVal.size()==1) {
        grid[i][j]=*(possVal.begin());
        return *(possVal.begin());
    }
    return false;
}
int main() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cin >> grid[i][j];
        }
    }
    while(true) {
        bool found = false;
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                if(grid[i][j]==0) {
                    if(poss(i,j)) found=true;
                } 
            }
        }

    }
}