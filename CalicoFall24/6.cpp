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
signed main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    // freopen("input.txt" , "r" , stdin);
    // freopen("output.txt" , "w", stdout);
    int T;
    cin >> T;
    vt<int> primes(3401);
    // int[] primes = new int[3401];
    primes[0] = 2;
    int index = 1;
    for(int i = 3; i * i <= 1000000000; i++) {
      bool prime = true;
      for(int j = 0; primes[j]*primes[j] <= i; j++) {
        if(i % primes[j] == 0) {prime = false; break;}
      }
      if(prime) {primes[index] = i; index++;}
    }

    int x = 1;
    int total = 0;
    vt<int> phi(57358), sumphi(57358);
    // int[] phi = new int[57358];
    // int[] sumphi = new int[57358];
    while(total < 1000000000) {
      x++;
      int temp = x;
      int phii = 1;
      index = 0;
      while(primes[index] * primes[index] <= temp) {
        if(temp % primes[index] == 0) {
          while(temp % primes[index] == 0) {
            temp /= primes[index];
            phii *= primes[index];
          }
          phii /= primes[index];
          phii *= primes[index] - 1;
        }
        index++;
      }
      if(temp > 1) {
        phii *= temp - 1;
      }
      phi[x] = phii;
      total += phii;
    }

    for(int i = 2; i < sumphi.size(); i++) {
      sumphi[i] = sumphi[i - 1] + phi[i];
    }

    while(T-- > 0) {
    //   st = new StringTokenizer(rr.readLine());
    //   int n = Integer.parseInt(st.nextToken());
      int n;
      cin >> n;
      int left = 1;
      int right = phi.size() - 1;
      while(right - left > 1) {
        int test = (left + right)/2;
        if(sumphi[test] >= n) {
          right = test;
        } else {
          left = test;
        }
      }
      n -= sumphi[left];
      vt<int> factors;
    //   ArrayList<Integer> factors = new ArrayList<Integer>();
      index = 0;
      int temp = right;
      while(primes[index] * primes[index] <= temp) {
        if(temp % primes[index] == 0) {
          factors.add(primes[index]);
          while(temp % primes[index] == 0) {
            temp /= primes[index];
          }
        }
        index++;
      }
      if(temp > 1) {factors.add(temp);}
      int top = 1;
      for(int i = 0; i < factors.size(); i++) {top *= 2;}

      int small = 0;
      int big = right;
      while(big - small > 1) {
        int test = (small + big)/2;
        int amount = 0;
        for(int iter = 0; iter < top; iter++) {
          int it = iter;
          bool pos = true;
          int divisor = 1;
          int primeIndex = 0;
          while(it > 0) {
            if(it % 2 == 1) {
              pos = !pos;
              divisor *= factors[primeIndex];
            }
            primeIndex++;
            it /= 2;
          }
          if(pos) {amount += test/divisor;}
          else {amount -= test/divisor;}
        }
        if(amount >= n) {big = test;}
        else {small = test;}
      }
      cout << big << " " << right-big << endl;
    //   pw.println(big + " " + (right - big));
    }

    // pw.close();
    return 0;
}