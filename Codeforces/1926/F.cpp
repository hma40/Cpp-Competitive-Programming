#include <bits/stdc++.h>
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
ll mod = 1000000007;
ll inf = 1e18;
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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
template<typename K, typename V> std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m) {
    os << "{ ";
    for(const auto& pair : m) {
        os << pair.first << " : " << pair.second << ", ";
    }
    os << "}";
    return os;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int t;
    cin >> t;
    vt<int> popCount(128);
    F0R(i, 128) {
        F0R(j, 7) {
            if(i&(1<<j)) popCount[i]++;
        }
    }
    while(t--) {
        vt<string> v(7);
        F0R(i, 7) cin >> v[i];
        vt<vt<int>> sides(16, vt<int>(4, -1));
        vt<vt<int>> mids(8, vt<int>(8, -1));
        int side = 0, mid = 0;
        int sCount = 0, mCount = 0;
        F0R(i, 4) {
            if(v[2*i][0]=='B') {
                side|=1<<i;
                sCount++;
            }
        }
        F0R(i, 3) {
            if(v[2*i+1][0]=='B') {
                mCount++;
                mid|=1<<i;
            }
        }
        F0R(i, 16) {
            if((i&side)==i) {
                sides[i][0]=sCount-popCount[i];
            }
        }
        F0R(i, 8) {
            if((i&mid)==i) {
                mids[i][0]=mCount-popCount[i];
            }
        }
        // cout << sides << endl << mids << endl;
        FOR(col, 1, 7) {
            vt<vt<int>> tempsides(16, vt<int>(4, -1)), tempmids(8, vt<int>(8, -1));
            side = 0;
            mid = 0;
            sCount = 0;
            mCount = 0;
            F0R(i, 4) {
                if(v[2*i][col]=='B') {
                    side|=1<<i;
                    sCount++;
                }
            }
            F0R(i, 3) {
                if(v[2*i+1][col]=='B') {
                    mCount++;
                    mid|=1<<i;
                }
            }
            F0R(mask, 16) {
                F0R(midMask, 4) {
                    if((mask&side)!=mask) continue;
                    if((mask&(midMask*2))!=(midMask*2)) continue;
                    int cn = popCount[mask];
                    int ans = 1e9;
                    F0R(lastMid, 8) {
                        F0R(lastDanger, 8) {
                            if(mids[lastMid][lastDanger]==-1) continue;
                            if(lastDanger&1) {
                                if((mask&1)&&(mask&2)) continue;
                            }
                            if(lastDanger&2) {
                                if((mask&4)&&(mask&2)) continue;
                            }
                            if(lastDanger&4) {
                                if((mask&4)&&(mask&8)) continue;
                            }
                            if(midMask&1) {
                                if(((lastMid&1)==0)||((lastMid&2)==0)) continue;
                            }
                            if(midMask&2) {
                                if(((lastMid&4)==0)||((lastMid&2)==0)) continue;
                            }
                            if((midMask&1)==0&&(mask&2)) {
                                if((lastMid&1)&&(lastMid&2)) continue;
                            }
                            if((midMask&2)==0&&(mask&4)) {
                                if((lastMid&4)&&(lastMid&2)) continue;
                            }
                            // if(col==3&&mask==4&&midMask==0) cout << lastMid << " " << lastDanger << endl;
                            ans=min(ans, mids[lastMid][lastDanger]);
                        }
                    }
                    if(ans!=1e9) {
                        tempsides[mask][midMask]=ans+sCount-cn;
                    }
                }
            }
            F0R(mask, 8) {
                F0R(midMask, 8) {
                    if((mask&mid)!=mask) continue;
                    if((mask&midMask)!=midMask) continue;
                    int cn = popCount[mask];
                    int ans = 1e9;
                    F0R(lastMid, 16) {
                        F0R(lastDanger, 4) {
                            if(sides[lastMid][lastDanger]==-1) continue;
                            if(lastDanger&1) {
                                if((mask&1)&&(mask&2)) continue;
                            }
                            if(lastDanger&2) {
                                if((mask&4)&&(mask&2)) continue;
                            }
                            if(midMask&1) {
                                if(((lastMid&1)==0)||((lastMid&2)==0)) continue;
                            }
                            if(midMask&2) {
                                if(((lastMid&4)==0)||((lastMid&2)==0)) continue;
                            }
                            if(midMask&4) {
                                if(((lastMid&4)==0)||((lastMid&8)==0)) continue;
                            }
                            if((midMask&1)==0&&(mask&1)) {
                                if((lastMid&1)&&(lastMid&2)) continue;
                            }
                            if((midMask&2)==0&&(mask&2)) {
                                if((lastMid&4)&&(lastMid&2)) continue;
                            }
                            if((midMask&4)==0&&(mask&4)) {
                                if((lastMid&4)&&(lastMid&8)) continue;
                            }
                            ans=min(ans, sides[lastMid][lastDanger]);
                        }
                    }
                    if(ans!=1e9) {
                        tempmids[mask][midMask]=ans+mCount-cn;
                    }
                }
            }
            swap(mids, tempmids);
            swap(sides, tempsides);
        //     cout << "---------" << col << "--------" << endl;
        //     F0R(i, 16) {
        //         F0R(j, 4) {
        //             if(sides[i][j]!=-1) {
        //                 cout << i << " " << j << " " << sides[i][j] << endl;
        //             }
        //         }
        //     }
        // //     cout << "********************" << endl;
        // //     F0R(i, 8) {
        // //         F0R(j, 8) {
        // //             if(mids[i][j]!=-1) {
        // //                 cout << i << " " << j << " " << mids[i][j] << endl;
        // //             }
        // //         }
        // //     }
        // //     cout << "---------------------------" << endl;
        // // }
        // //     cout << "---------" << 6 << "--------" << endl;
        // //     F0R(i, 16) {
        // //         F0R(j, 4) {
        // //             if(sides[i][j]!=-1) {
        // //                 cout << i << " " << j << " " << sides[i][j] << endl;
        // //             }
        // //         }
        // //     }
        // //     cout << "********************" << endl;
        // //     F0R(i, 8) {
        // //         F0R(j, 8) {
        // //             if(mids[i][j]!=-1) {
        // //                 cout << i << " " << j << " " << mids[i][j] << endl;
        // //             }
        // //         }
        // //     }
        // //     cout << "---------------------------" << endl;
        }
        int ans = 0;
        int ad = 1e9;
        F0R(i, 16) {
            F0R(j, 4) {
                if(sides[i][j]==-1) continue;
                ad=min(ad, sides[i][j]);  
            }
        }
        ans+=ad;
        ad=1e9;
        F0R(i, 8) {
            F0R(j, 8) {
                if(mids[i][j]==-1) continue;
                ad=min(ad, mids[i][j]);
            }
        }
        ans+=ad;
        cout << ans << endl;
    }
    return 0;
}