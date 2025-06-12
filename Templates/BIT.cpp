template<typename T>
class FenwickTree {
private:
    int n;
    std::vector<T> bit;  // 1-based Fenwick tree array
    std::vector<T> arr;  // underlying array to track current values

public:
    // Construct a Fenwick Tree of size _n (0-based interface, internally 1-based)
    FenwickTree(int _n)
        : n(_n),
          bit(n + 1, T()),
          arr(n, T())
    {}

    // add(index, x): increase the value at index 'idx' (0-based) by 'v'
    void add(int idx, T v) {
        assert(idx >= 0 && idx < n);
        arr[idx] += v;
        int i = idx + 1;  // switch to 1-based
        while (i <= n) {
            bit[i] += v;
            i += (i & -i);
        }
    }

    // set(index, x): set the value at index 'idx' (0-based) to 'v'
    void set(int idx, T v) {
        assert(idx >= 0 && idx < n);
        T delta = v - arr[idx];
        add(idx, delta);
    }

    // prefix_sum(idx): returns sum of elements from 0 to idx (inclusive)
    T prefix_sum(int idx) const {
        assert(idx >= 0 && idx < n);
        T result = T();
        int i = idx + 1;  // switch to 1-based
        while (i > 0) {
            result += bit[i];
            i -= (i & -i);
        }
        return result;
    }

    // sum(left, right): returns sum of elements from left to right (inclusive)
    T sum(int left, int right) const {
        assert(left >= 0 && right < n && left <= right);
        if (left == 0) {
            return prefix_sum(right);
        } else {
            return prefix_sum(right) - prefix_sum(left - 1);
        }
    }
};
