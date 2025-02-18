#include <bits/stdc++.h>
std::string to_string(__int128_t value) {
    if (value == 0) return "0";
    
    std::string result;
    bool negative = (value < 0);
    if (negative) value = -value;
    
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }
    
    if (negative) result += '-';
    
    std::reverse(result.begin(), result.end());
    return result;
}

// Overload << operator for __int128
std::ostream& operator<<(std::ostream& os, __int128_t value) {
    return os << to_string(value);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::multiset<T>& s) {
    os << "{ ";
    for(const auto& elem : s) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, std::queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::deque<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::stack<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> q) {
    // Print each element in the queue
    os << "{ ";
    while (!q.empty()) {
        os << q.top() << " ";
        q.pop();
    }
    os << "}";
    // Print a newline at the end
    return os;
}

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
template<typename T>
using min_pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;
using namespace std;
using ll = long long;
#define add push_back 
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define f first
#define s second
#define trav(a,x) for (auto& a: x)
#define int long long
#define vt vector
#define endl "\n"
#define double long double
ll mod = 1000000007;
ll inf = 1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
int toint(array<int,8> &a) {
    int ans = 0;
    int pow = 1;
    F0R(i, 8) {
        ans+=pow*a[i];
        pow*=5;
    }
    return ans;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    vector<int> dist(390625, -1);
    queue<int> q;
    array<int,8> identity = {0,1,2,3,0,1,2,3};
    deque<pair<array<int,8>,int>> dq;
    F0R(mask, 256) {
        array<int,8> temp = identity;
        F0R(i, 8) {
            if(mask&(1<<i)) {
                temp[i]=4;
            }
        }
        int num = toint(temp);
        dist[num]=0;
        dq.push_back({temp,num});
    }
    array<int,8> interested = {0,4,4,2,4,4,4,1};
    //map: (x,y,m)->(c,d). ALWAYS x,y,m
    while(dq.size()) {
        auto tp = dq.front().f;
        auto num = dq.front().s;
        dq.pop_front();
        //x=x&y
        /*
        (0,0)->(0,0)
        (0,1)->(0,1)
        (1,0)->(0,0)
        (1,1)->(1,1)
        */
        array<int,8> nw;
        if(tp[1]==4&&tp[5]==4) {
            nw[2]=tp[2];
            nw[3]=tp[3];
            //tp[3] can be nw[2] or nw[3]
            nw[6]=tp[6];
            nw[7]=tp[7];
            if(tp[0]==4&&tp[4]==4) {
                nw[0]=4;
                nw[1]=4;
                nw[4]=4;
                nw[5]=4;
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.1" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else if(tp[0]==4) {
                nw[0]=4;
                nw[1]=4;
                //try nw[7]=nw[6]=tp[7]
                nw[4]=tp[4];
                nw[5]=tp[4];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.2" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[7]=tp[7] and nw[6]=4
                nw[4]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.3" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[6]=tp[7] and nw[7]=4
                nw[5]=4;
                nw[4]=tp[4];
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.4" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else if(tp[4]==4) {
                nw[4]=4;
                nw[5]=4;
                //try nw[7]=nw[6]=tp[7]
                nw[0]=tp[0];
                nw[1]=tp[0];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.5" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[7]=tp[7] and nw[6]=4
                nw[0]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.6" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[6]=tp[7] and nw[7]=4
                nw[1]=4;
                nw[0]=tp[0];
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.7" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else {
                nw[0]=tp[0];
                nw[1]=tp[0];
                nw[4]=tp[4];
                nw[5]=tp[4];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.8" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[0]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.9" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[0],nw[1]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.10" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[0]=tp[0];
                nw[1]=tp[0];
                nw[4]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.11" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[4],nw[5]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.12" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[0]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.13" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[0],nw[1]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.14" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[5],nw[4]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.15" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[0],nw[1]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 1.16" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            }
        }
        /*
        x=x|y
        (0,0)->(0,0)
        (0,1)->(1,1)
        (1,0)->(1,0)
        (1,1)->(1,1)
        */
        if(tp[2]==4&&tp[6]==4) {
            nw[0]=tp[0];
            nw[1]=tp[1];
            //tp[3] can be nw[2] or nw[3]
            nw[4]=tp[4];
            nw[5]=tp[5];
            if(tp[3]==4&&tp[7]==4) {
                nw[3]=4;
                nw[2]=4;
                nw[7]=4;
                nw[6]=4;
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.1" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else if(tp[3]==4) {
                nw[3]=4;
                nw[2]=4;
                //try nw[7]=nw[6]=tp[7]
                nw[7]=tp[7];
                nw[6]=tp[7];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.2" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[7]=tp[7] and nw[6]=4
                nw[6]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.3" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[6]=tp[7] and nw[7]=4
                nw[7]=4;
                nw[6]=tp[7];
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.4" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else if(tp[7]==4) {
                nw[7]=4;
                nw[6]=4;
                //try nw[7]=nw[6]=tp[7]
                nw[3]=tp[3];
                nw[2]=tp[3];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.5" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[7]=tp[7] and nw[6]=4
                nw[2]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.6" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                //try nw[6]=tp[7] and nw[7]=4
                nw[3]=4;
                nw[2]=tp[3];
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.7" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            } else {
                nw[2]=tp[3];
                nw[3]=tp[3];
                nw[6]=tp[7];
                nw[7]=tp[7];
                int number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.8" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[2]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.9" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[2],nw[3]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.10" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[2]=tp[3];
                nw[3]=tp[3];
                nw[6]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.11" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[6],nw[7]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.12" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                nw[2]=4;
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.13" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[2],nw[3]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.14" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[6],nw[7]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.15" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
                swap(nw[2],nw[3]);
                number = toint(nw);
                if(dist[number]==-1) {
                    if(nw==interested) {
                        cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 2.16" << endl;
                    }
                    dist[number]=dist[num]+1;
                    dq.push_back({nw,number});
                }
            }
        }
        /*
        y=x xor y
        (0,0)->(0,0)
        (0,1)->(0,1)
        (1,0)->(1,1)
        (1,1)->(1,0)
        */
        nw[0]=tp[0];
        nw[1]=tp[3];
        nw[2]=tp[2];
        nw[3]=tp[1];
        nw[4]=tp[4];
        nw[5]=tp[7];
        nw[6]=tp[6];
        nw[7]=tp[5];
        int number = toint(nw);
        if(dist[number]==-1) {
            if(nw==interested) {
                cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPERATION 3" << endl;
            }
            dist[number]=dist[num]+1;
            dq.push_back({nw,number});
        }
        /*
        y = y xor m
        (0,0,0)->(0,0,0)
        (0,0,1)->(0,1,1)
        (0,1,0)->(0,1,0)
        (0,1,1)->(0,0,1)
        (1,0,0)->(1,0,0)
        (1,0,1)->(1,1,1)
        (1,1,0)->(1,1,0)
        (1,1,1)->(1,0,1)
        */
        nw[0]=tp[0];
        nw[1]=tp[1];
        nw[2]=tp[2];
        nw[3]=tp[3];
        nw[4]=tp[6];
        nw[5]=tp[7];
        nw[6]=tp[4];
        nw[7]=tp[5];
        number=toint(nw);
        if(dist[number]==-1) {
            if(nw==interested) {
                cerr << "FROM " << tp << dist[num] << " TO " << nw << "OPErATION 4 " << endl;
            }
            dq.push_back({nw,number});
            dist[number]=dist[num]+1;
        }
    }
    // array<int,8> arr = {0,4,4,4,4,3,4,4};
    // cout << dist[toint(arr)] << endl;
    int t = 1;
    cin >> t;
    while(t--) {
        int a,b,c,d,m;
        cin >> a >> b >> c >> d >> m;
        array<int,8> here;
        F0R(i, 8) here[i]=4;
        bool bad = false;
        F0R(i, 30) {
            bool aa = a&(1<<i), bb = b&(1<<i), cc = c&(1<<i), dd = d&(1<<i), mm = m&(1<<i);
            int mp = aa+bb*2+mm*4;
            int val = cc+2*dd;
            if(here[mp]!=4&&here[mp]!=val) bad=true;
            else here[mp]=val;
        }        
        // cout << here << endl;
        if(bad) {
            cout << -1 << endl;
        } else {
            cout << dist[toint(here)] << endl;
        }
    }
    return 0;
}