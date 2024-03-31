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

// Slide Window
class Solution {
public:
    int minOperations(int n) {
        string str;
        while(n != 0){
            if(n&1){
                str.push_back('1');
            }
            else str.push_back('0');
            n /= 2;
        }

        int res = 0;
        int j = 0;
        
        // 111001
       
        for(int i = 0; i < str.size(); i++){
            j = max(i,j);
            while(j < str.size() && str[j] == '1'){
                j++;
            }
            // 111001
            if(j-i >= 2) {
                if(j < str.size()){
                    res += 1;
                    str[j] = '1';
                }
                else {
                    res += 2;
                    break;
                }
                i = j - 1;
            }
            else if(j-i == 1){
                res += 1;
                i = j-1;
            } 

        }

        return res;
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
