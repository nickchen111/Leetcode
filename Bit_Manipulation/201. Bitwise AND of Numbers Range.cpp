/*
201. Bitwise AND of Numbers Range
*/

// TC:O(32) SC:O(1)
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int res = 0;
        for(int i = 31; i >= 0; i--){
            int tmp1 = ((left>>i)&1);
            int tmp2 = ((right>>i)&1);
            if( tmp1 == tmp2 && tmp1 != 0){
                res += (1 << i);
            }
            else if(tmp1 != tmp2) break;
        }

        return res;
    }
};

/*
AND
1 & 1 -> 1
1 & 0 -> 0其餘都是0

1 -> 01
2 -> 10
3 -> 11
4 -> 100...
5 -> 101
一定會經過1000 [5 11] -> ans : 0 
11->1101

求某個連續區間中所有數字AND結果 先想AND特性 只要其中一個有0就會變成0 從某個數字到某個數字 如果希望AND完不是0那他們共同前綴有哪些就決定AND後結果是哪些
 因為在共同前綴的結果 從left 走到right一定會經過共同前綴之後是0的情況
*/
