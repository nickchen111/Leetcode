/*
3370. Smallest Number With All Set Bits
*/

// TC : O(lgn) SC:O(1)
class Solution {
public:
    int smallestNumber(int n) {
        int res = 0;
        int count = 0;
        while(n) {
            res += (1 << count);
            n >>= 1;
            count += 1;
        }
        
        return res;
    }
};


// TC:O(1) SC:O(1)
class Solution {
public:
    int smallestNumber(int n) {
        return (1 << bit_width((unsigned) n)) - 1;
    }
};
