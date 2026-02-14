class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>> dp(100, vector<double>(100));
        dp[0][0] = poured;
        for(int i = 0; i < 99; i++){
            for(int j = 0; j <= i; j++){
                if(dp[i][j] > 1){
                    dp[i+1][j] += (dp[i][j]-1)/2.0;
                    dp[i+1][j+1] += (dp[i][j]-1)/2.0;
                }
            }
        }

        return min(1.0, dp[query_row][query_glass]);
    }
};



/*
            1 (1)
         |.     |
         1.     1  (0 1 0) -> (1 1)
      |.       |.  .  | (1 2 1)
    0.5     1     0.5
  |.     |.       |.     | ->(1  3  3  1 )
|.  |       |.      |.    |(0.5 2, 3. 2 0.5) -> (1 4, 6, 4, 1)
row = 5 (1 5 6 6 5 1) row/2
row = 6 (1 6 11 6 5 1)
row = 7 (1 7 )
每一層的下一次比例就會是 上一層的 1, 3+1,3+3,3+1,1
所以每一杯都會有左邊的1/2 右的1/2
要問說某一row 某個glass他在倒了poured瓶香檳後可以裝多滿
這題感覺可以用模擬的方式做出來 也可以用DP
*/