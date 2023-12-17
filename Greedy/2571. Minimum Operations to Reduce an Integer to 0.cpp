/*
2571. Minimum Operations to Reduce an Integer to 0
*/

// TC:O(32*32) SC:O(1)
class Solution {
public:
    int minOperations(int n) {
        int res = 0;
        for(int i = 0; i < 32; i++){
            if(countOne(n + (1<<i)) +1 <= countOne(n)){
                n += (1<<i);
                res += 1;
            }
        }

        return res + countOne(n);
    }
    int countOne(int n){
        return __builtin_popcount(n);
    }
};

/*
39 -> 0 1 0 0 1 1 1 
40 -> 0 1 0 1 0 0 0 
有一種想將數字連續超過3個的1找出來 給他加上位階當前最低數字他會變成只有1個1
如此這題就變成 單個1 or 2個 1單獨加 連續超過3個的只加2 但是如果間隔一個0的也有連續1

54 -> 1 1 0 1 1 0
      0 1 0 1 1 0 max: 3 min : 3 
      1 1 0 1 0 0 max: 3 min : 3
    1 1 1 0 1 0 0 max: 3 min : 3
    only now count >= 2 跟後面連結才有意義
    1 1 1 0 1 0 0 0 
    那就直接想說如果當前最低為加了一個數字 能讓1的數量變少或者一樣 那就去做 一樣的原因是 也許會幫到後面的
    進位總是有好處

*/
