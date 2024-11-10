/*
3345. Smallest Divisible Digit Product I
*/

// TC:O(m * lgn) SC:O(1)
class Solution {
public:
    int smallestNumber(int n, int t) {
        for (int i = n; ; i++) {
            int prod = 1;
            for (int x = i; x; x /= 10) {
                prod *= x % 10;
            }
            if (prod % t == 0) {
                return i;
            }
        }
        
        return -1;
    }
};
