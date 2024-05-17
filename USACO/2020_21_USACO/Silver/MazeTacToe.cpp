#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

int pow3[10];
vector<vector<string>> board;
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
bool visite[25][25][19683] = {{{false}}};
unordered_set<string> winningBoard;
bool makesMoo(string s, int a, int b, int c) {
    return (s[a]=='2'&&s[b]=='1'&&s[c]=='1')||(s[a]=='1'&&s[b]=='1'&&s[c]=='2');
}
bool winning(string s) {
    return makesMoo(s,0,1,2)||makesMoo(s,6,7,8)||makesMoo(s,3,4,5)||makesMoo(s,0,3,6)||makesMoo(s,1,4,7)||makesMoo(s,2,5,8)||makesMoo(s,0,4,8)||makesMoo(s,2,4,6);
}
int convert(string s) {
    int ans = 0;
    for(int i = 0; i < 9; i++) {
        ans+=s[i]*pow3[i];
    }
    return ans;
}
void fills(int x, int y, string s) {
    //std::cout << x << " " << y << " " << s << endl;
    if(winning(s)) {
        winningBoard.insert(s);
        return;
    }
    for(int i = 0; i < 4; i++) {
        string t = s;
        int newx = x+dx[i];
        int newy = y + dy[i];
        if(board[newx][newy]!="###") {
            if(board[newx][newy][0]=='O') {
                int a = board[newx][newy][1]-'1';
                int b = board[newx][newy][2]-'1';
                int n = 3*a+b;
                if(t[n]=='0') {
                    t[n]='1';
                }
            }
            if(board[newx][newy][0]=='M') {
                //std::cout << " got here " << endl;
                int a = board[newx][newy][1]-'1';
                int b = board[newx][newy][2]-'1';
                int n = 3*a+b;
                if(t[n]=='0') {
                    //std::cout << "got here 2 " << " " << t << " " << n << " " << t[n] << " " << newx << " " << newy << endl;
                    t[n]='2';
                }
            }
            int converted = convert(t);
            //std::cout << x << " " << y << " " << s << " " << newx << " " << newy << " " << t << " bruh" << " " << i << endl;
            if(!visite[newx][newy][converted]) {
                visite[newx][newy][converted]=true;
                fills(newx,newy,t);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int hm = 1;
    for(int i = 0; i < 10; i++) {
        pow3[i]=hm;
        //cout << pow3[i] << endl;
        hm*=3;
    }
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        vector<string> temp(n);
        board.push_back(temp);
    }
    int x=0,y=0;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < n; j++) {
            board[i][j]=s.substr(3*j, 3);
            if(board[i][j]=="BBB") {
                x=i;
                y=j;
            }
        }
    }
    visite[x][y][0]=true;
    fills(x,y,"000000000");
    std::cout << winningBoard.size() << endl;
}
