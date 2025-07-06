// TC:O(logn) SC:O(logn) 
class Solution {
    string base_repr(int v, int base) {
        string s;
        while (v > 0) {
            int d = v % base;
            s += d < 10 ? '0' + d : 'A' + d - 10;
            v /= base;
        }
        ranges::reverse(s);
        return s;
    }

public:
    string concatHex36(int n) {
        return base_repr(n * n, 16) + base_repr(n * n * n, 36);
    }
};
