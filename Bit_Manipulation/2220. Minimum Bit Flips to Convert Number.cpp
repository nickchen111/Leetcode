/*
2220. Minimum Bit Flips to Convert Number
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int num = start^goal;
        int count = __builtin_popcount(num);

        return count;
    }
};
