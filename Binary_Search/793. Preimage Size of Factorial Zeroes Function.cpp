/*
793. Preimage Size of Factorial Zeroes Function
*/

//TC:O(lgn) SC:O(1)
class Solution {
public:
    int preimageSizeFZF(int k) {
        long left = 0; long right = 5e9;

        while(left < right){
            long mid = left + (right - left)/2;

            if(countTrailingZeroes(mid) > k) right = mid -1;
            else if(countTrailingZeroes(mid) < k) left = mid+1;
            else right = mid;//想找最小的那項
        }

        if(left > right) return 0;
        if(countTrailingZeroes(left) == k && left == right) return 5;
        else return 0;
    }

    long countTrailingZeroes(long mid){
        long divisor = 5;
        long res = 0;
        while(mid >= divisor){
            res += mid/divisor;
            divisor*=5;
        }

        return res;
    }
};

/*
此題為數學題結合binary search
考點在於要考慮到二分搜索完之後是否搜到的是正確答案->代表此題可能有找不到的狀況
*/
