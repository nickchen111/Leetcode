/*
3129. Find All Possible Stable Binary Arrays I
*/

// TC:O(n^3) SC:O(n^2)
class Solution {
    using LL = long long;
    LL dp1[1005][1005];
    LL dp0[1005][1005];
    LL M = 1e9+7;
public:
    int numberOfStableArrays(int zero, int one, int limit) {
  
        dp0[0][0] = 1;
        dp1[0][0] = 1;
        
        for(int i = 0; i <= zero; i++){
            for(int j = 0; j <= one; j++){
                if(i == 0 && j == 0) continue;
                for(int k = 1; k <= limit; k++){
                    if(i >= k) dp0[i][j] += dp1[i-k][j];
                    if(j >= k) dp1[i][j] += dp0[i][j-k];
                    dp0[i][j] %= M;
                    dp1[i][j] %= M;
                }
            }
        }
        
        return (dp0[zero][one] + dp1[zero][one]) % M;
        
    }
};

/*
zero = 3, one = 3, limit = 2
並且還想知道剩下多少個0 1
總共用了多少個 還剩多少個0 以及結尾是啥數字
x x x 
0 1 
1 0 
0 0
1 1 

必須要有限定數量的0 & 1
然後不能有連續出現相同元素次數超過limit
dp0[i][j]: the total number of stable binary arrays, and ending at 0
dp1[i][j]: the total number of stable binary arrays, and ending at 1

dp1[i][j] dp0[i-limit][j] + dp0[i-limit+1][j] + ... + dp1[i-1][j];
dp0[i][j] dp1[i][j-limit] + dp1[i][j-limit+1] + ... + dp0[i][j-1];
改進的地方就是會發現k=1 ~ limit 就是一段連續的區間 用presum去做
*/
