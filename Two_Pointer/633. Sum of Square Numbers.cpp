/*
633. Sum of Square Numbers
*/

// TC:O(sqrt(n)) SC:O(1)
class Solution {
    using LL = long long;
public:
    bool judgeSquareSum(int c) {
        LL right = sqrt(c);
        LL left = 0;
        while(left <= right){
            if(left*left + right*right == c) return true;
            else if(left*left + right*right < c){
                left++;
            }
            else right--;
        }

        return false;
    }
};
