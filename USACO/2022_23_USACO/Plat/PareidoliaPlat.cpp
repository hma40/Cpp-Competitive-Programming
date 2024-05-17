#include <iostream>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
int n;
void printArray(vector<long long> &v) {
    cout << '[';
    for(long long l: v) cout << l << ", ";
    cout << ']' << endl;
}
struct Matrix {
    vector<vector<long long>> data;
    void print() {
        for(vector<long long> d: data) printArray(d);
    }
    Matrix() {
        data.resize(8, vector<long long>(8));
    }
    Matrix(int type, int index) {
        data.resize(8, vector<long long>(8));
        for(int i = 0; i < 8; i++) {
            data[i][i]=1;
        }
        data[0][7]=1;
        if(type=='b') {
            //b
            data[0][7]=0;
            data[0][0]=0;
            data[1][0]=1;
            data[1][7]=1;
        } else if(type=='e') {
            //e
            data[1][1]=0;
            data[5][5]=0;
            data[2][1]=1;
            data[0][5]=1;
            data[6][5]=n-index;
        } else if(type=='s') {
            //s
            data[3][2]=1;
            data[4][3]=1;
            data[2][2]=0;
            data[3][3]=0;
        } else if(type=='i') {
            //i
            data[5][4]=1;
            data[4][4]=0;
        } else if(type==-1) {
            //ident
            data[0][7]=0;
        }
    }
    Matrix(const Matrix& other) {
        data.resize(8, vector<long long>(8));
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    static Matrix mult(const Matrix& a, const Matrix& b) {
        Matrix ret;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                ret.data[i][j] = 0;
                for (int k = 0; k < 8; k++) {
                    ret.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return ret;
    }
};

struct SegTree {
    int n;
    vector<Matrix> tree;
    vector<int> begin, end;
    void print() {
        for(Matrix m: tree) {
            m.print();
            cout << endl;
        }
    }
    SegTree(int nn): n(nn){
        while (n != (n & (-n))) n++;
        tree.resize(2 * n);
        for (int i = 1; i < 2 * n; i++) {
            tree[i] = Matrix(-1,0);
        }
        begin.resize(2 * n);
        end.resize(2 * n);
        for (int i = n; i < 2 * n; i++) {
            begin[i] = end[i] = i - n;
        }
        for (int i = n - 1; i > 0; i--) {
            begin[i] = begin[2 * i];
            end[i] = end[2 * i + 1];
        }
    }

    void update(int index, int character, int i) {
        if (i >= n) {
            tree[i] = Matrix(character, index);
            return;
        }
        if (begin[2 * i] <= index && end[2 * i] >= index) {
            update(index, character, 2 * i);
        } else {
            update(index, character, 2 * i + 1);
        }
        tree[i] = Matrix::mult(tree[2 * i + 1], tree[2 * i]);
    }

    long long query() {
        return tree[1].data[6][7];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    cin >> word;
    string ans = "";
    n=word.length();
    SegTree st(n);
    for (int i = 0; i < n; i++) {
        st.update(i, word[i], 1);
    }
    ans+=to_string(st.query())+"\n";

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int index;
        cin >> index;
        char character;
        cin >> character;
        st.update(index - 1, character, 1);
        ans+=to_string(st.query())+"\n";
    }
    cout << ans;

    return 0;
}