/*
440. K-th Smallest in Lexicographical Order
*/

// TC:O(lgn * lgn) SC:O(lgn)
class Solution {
    using LL = long long;
public:
    int findKthNumber(int n, int k) {
        return FindKthNumberBeginWith(0, n, k);
    }

    // ~= 10^2
    // return the Lexicographically k-th element that begins with prefix
    // if k==0, return prefix itself
    int FindKthNumberBeginWith(int prefix, int n, int k){
        if(k == 0) return prefix;
        int start = (prefix == 0 ? 1 : 0);

        for(int i = start; i <= 9; i++){
            // 1 表示目前的數字就是結尾的狀況
            int count = 1 + TotalNumbersBeginWith(prefix*10+i, n);

            if(count < k){
                k -= count;
            }
            else {
                return FindKthNumberBeginWith(prefix*10+i, n, k-1);
            }
        }

        return -1;
    }

    // return how many numbers that begin with prefix (and <= n)
    // excluding prefix itself
    int TotalNumbersBeginWith(int prefix, int n){
        
        LL exp = 10;
        LL count = 0;
        while(1){
            LL lower = prefix*exp;
            LL upper = prefix*exp + exp - 1;

            if(lower > n) break;
            // 5050, 4050 -> 101
            else if(lower <= n && upper >= n){
                count += (n-lower+1);
                break;
            }
            else {
                count += exp;
            }
            exp *= 10;
        }

        return count;
    }
};
