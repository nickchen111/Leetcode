/*
3130. Find All Possible Stable Binary Arrays II
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
    using LL = long long;
    LL dp1[1005][1005];
    LL dp0[1005][1005];
    LL M = 1e9+7;
    LL presum0[1005][1005];
    LL presum1[1005][1005];
public:
    int numberOfStableArrays(int zero, int one, int limit) {
  
        dp0[0][0] = 1;
        dp1[0][0] = 1;
        presum0[0][0] = 1;
        presum1[0][0] = 1;

        for(int i = 0; i <= zero; i++){
            for(int j = 0; j <= one; j++){
                if(i == 0 && j == 0) continue;
                dp0[i][j] = (i-1 < 0 ? 0 : presum1[j][i-1] ) - (i-limit-1 < 0 ? 0 : presum1[j][i-limit-1]); // 這裡的第一個下標是j 有點反直覺
                dp1[i][j] = (j-1 < 0 ? 0: presum0[i][j-1] ) - (j-limit-1 < 0 ? 0 : presum0[i][j-limit-1]);
                dp0[i][j] = (dp0[i][j]+M) % M;
                dp1[i][j] = (dp1[i][j]+M) % M;
                presum0[i][j] = (j-1 < 0 ? 0 : presum0[i][j-1]) + dp0[i][j];
                presum1[j][i] = (i-1 < 0 ? 0 : presum1[j][i-1]) + dp1[i][j];

                // presum0[i][j] %= M;
                // presum1[j][i] %= M;
            }
        }
        
        return (dp0[zero][one] + dp1[zero][one]) % M;
        
    }
};

/*
必須要有限定數量的0 & 1
然後不能有連續出現相同元素次數超過limit
dp0[i][j]: the total number of stable binary arrays, and ending at 0
dp1[i][j]: the total number of stable binary arrays, and ending at 1

dp1[i][j] dp0[i-limit][j] + dp0[i-limit+1][j] + ... + dp1[i-1][j];
dp0[i][j] dp1[i][j-limit] + dp1[i][j-limit+1] + ... + dp0[i][j-1];
改進的地方就是會發現k=1 ~ limit 就是一段連續的區間  用presum去做
*/
