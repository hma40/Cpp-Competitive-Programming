#include <bits/stdc++.h>
using namespace std;

int N;
int A[1000][1000];
int S[1000], T[1000];

int main(void) 
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    cin >> N;
    for (int i=0; i<N; i++) std::cin>>S[i];
    for (int i=0; i<N; i++) std::cin>>T[i];
    A[0][0] = abs(S[0]-T[0])<=4;
    for (int i=1; i<N; i++){
        if(abs(S[0]-T[i])<=4){
            A[0][i]=1;
        } else {
            A[0][i]=A[0][i-1];
        }
        if(abs(S[i]-T[0])<=4){
            A[i][0]=1;
        } else {
            A[i][0]=A[i-1][0];
        }
    }
    for (int i=1; i<N; i++){
        for (int j=1; j<N; j++){
            A[i][j] = max(A[i-1][j], A[i][j-1]);
            if(abs(S[i]-T[j])<=4) {
                A[i][j]=A[i-1][j-1]+1;
            }
        }
    } 
    std::cout << A[N-1][N-1] << endl;
    return 0;
}