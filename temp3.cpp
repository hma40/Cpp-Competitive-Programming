#include <bits/stdc++.h>
using namespace std;
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
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<
    decltype(std::begin(std::declval<T>())),
    decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// Generic container printer (vector, set, deque, array, map, etc.)
template <typename T>
typename std::enable_if<is_iterable<T>::value, ostream&>::type
operator<<(ostream& os, const T& container) {
    os << "{ ";
    for (auto it = std::begin(container); it != std::end(container); ++it) {
        os << *it;
        if (std::next(it) != std::end(container)) os << ", ";
    }
    os << " }";
    return os;
}

// Queue-like adapters (stack, queue, priority_queue)
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "{ ";
    while (!q.empty()) { os << q.front(); q.pop(); if (!q.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, stack<T> st) {
    os << "{ ";
    while (!st.empty()) { os << st.top(); st.pop(); if (!st.empty()) os << ", "; }
    os << " }";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, priority_queue<T> pq) {
    os << "{ ";
    while (!pq.empty()) { os << pq.top(); pq.pop(); if (!pq.empty()) os << ", "; }
    os << " }";
    return os;
}

// using namespace std;
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
// #define endl "\n"
#define enld "\n"
#define double long double
const ll mod = 998244353;
ll inf = 1e18;
vt<int> v(599);
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void fuck(int bad) {
    int n = (v.size()+1)/2;
		vt<int> ord;
		F0R(i, n) ord.add(i+1);
		int ql = 4*n;
    int lg = 1;
    while((1<<lg)<n) lg++;
    ql+=2*lg;
    cout << n << " " << ql << endl;
		shuffle(begin(ord),end(ord),rnd);
		// cout << ord << endl;
        int whichNum = 0;

    F0R(i, n) {
      if(ord[i]==bad) {
        cout << "bad is in position " << i << endl;
      }
    }
    // cout << "LINE 114" << endl;
    auto ask = [&](int x, const vt<int> &ind)->bool{
      if(!ql) {
        cout << "Got up to position " << whichNum << endl;
      }
      assert(ql);
			ql--;
			// cout << "? " << x << " " << ind.size() << " ";
			// trav(xx, ind) cout << xx+1 << " ";
			// cout << endl;
      trav(xx, ind) if(v[xx]==x) return true;
			// cin >> ans;
			return false;
		};
		auto complement = [&](const vt<int> &ind, vt<int> &all)->vt<int>{
			vt<bool> seen(n*2-1);
			trav(x, ind) seen[x]=true;
			vt<int> ret;
      vt<bool> seen2(n*2-1);
      trav(x, all) seen2[x]=true;
			F0R(i, n*2-1) if(!seen[i] && seen2[i]) ret.add(i);
      // cout << ind << all << ret << endl;
			return ret;
		};
		int ans = -1;
		trav(x, ord) {
      int used = 0;
      int qh = 0;
			vt<int> all;
			bool baad=false;
			F0R(i, n*2-1) all.add(i);
			while(all.size()>1) {
				shuffle(begin(all),end(all), rnd);
				vt<int> inds;
        int part = all.size()/2;
        part=min(part, (int)all.size()-1);
        part=max(part, 1LL);
				F0R(i, part) inds.add(all[i]);
				// cout << all.size() << " " << inds.size() << " " << ql << endl;
        qh++;
        if(ql==0) break;
        if(ask(x,inds)) {
					qh++;
          if(ql==0) break;
          if(ask(x, complement(inds, all))) {
						baad=true;
						break;
					} else {
						all=inds;
					}
				} else {
					all=complement(inds, all);
				}
			}
      // cout << "GOT TO LINE 150 " << endl;
			if(!baad) {
				ans=x;
				break;
			}
      // cout << "Number " << whichNum << " took " << qh << " queries " << endl;
      whichNum++;
		}
    cout << whichNum << endl;
		assert(ans==bad);
		cout << "! " << ans << endl;
    cout << "Queries used: " << 925-ql << endl;

}
int rand_num(int a, int b) {
    return rnd()%(b-a+1)+a;
}
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int tests = 0;
    while(true) {
      int n = rand_num(1,300);
      cout << "Test " << tests << ", n: " << n << ", Bad: ";
      tests++;
      int bad = rnd()%n+1;
      cout << bad << endl;
      v.resize(2*n-1);
      // v = vt<int>();
      int nxt = 0;
      F0R(i, n) {
        if(i+1==bad) {
          v[nxt++]=i+1;
        } else {
          v[nxt++]=i+1;
          v[nxt++]=i+1;
        }
      }
      shuffle(begin(v),end(v), rnd);
      fuck(bad);
    }
    return 0;
}
/*
we are expected to only have to ask for half of them
how many queries does each one take?
it halves each time

if this one is the answer 
then we go through all log levels
1/2 chance its 2 per level
1/2 chance its 1 per level
so when log=9 we expect <=15 queries

if this one isnt the answer
theres a 1/2 chance it ends
1/4 chance we ask once
1/4 chance we ask twice

yeah so on average we ask 4 times per number
4 * 150 + 15 <<< 925 so wtf

what if we split into three groups instead
we want to have average queries ~3

with 3 groups whats the chances it goes to a single one? 1/3
E = 1/3(E+3)+2/3(3)


E=p^2(E+1)+(1-p)^2(E+2)+2p(1-p)(2)

p^2+p^2-2p+1+2p-2p^2

E=1/4(E+1)+1/4(E+2)+
*/