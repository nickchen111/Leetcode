/*
191. Number of 1 Bits
*/

//n = n& (n-1)的位操作運用基礎題
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n!=0){
            n = n&(n-1);
            res++;
        }

        return res;
    }
};
