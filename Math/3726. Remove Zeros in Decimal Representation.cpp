// TC:O(logn) SC:O(1)
class Solution {
    using ll = long long;
public:
    long long removeZeros(long long n) {
        ll count = 1;
        ll ans = 0;
        while (n) {
            int re = n % 10;
            if (re != 0) {
                ans = ans + count * re;
                count *= 10;
            }
            n /= 10;
        }
       
        return ans;
    }
};
