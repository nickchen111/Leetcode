/*
629. K Inverse Pairs Array
*/

// 數學優化 TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int kInversePairs(int n, int k) {
        
        vector<vector<long>> dp(n+1, vector<long>(k+1,0));
        for(int i = 0; i <= n; i++){
            dp[i][0] = 1;
        } 

        int M = 1e9+7;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= k; j++){
                if(j >= i)
                    dp[i][j] = (dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i] + M) % M;
                else dp[i][j] = (dp[i][j-1] + dp[i-1][j]) % M;
               
            }
        }

        return dp[n][k];
    }
};


// TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int kInversePairs(int n, int k) {
        
        vector<vector<int>> dp(n+1, vector<int>(k+1,0));
        for(int i = 0; i <= n; i++){
            dp[i][0] = 1;
        } 

        int M = 1e9+7;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= k; j++){
                for(int m = 0; m <= min(j,i-1); m++){
                    dp[i][j] += dp[i-1][j-m];
                    dp[i][j] %= M;
                }
            }
        }

        return dp[n][k];
    }
};

/*
給你一個整數計算這個整數的排列組合中有多少滿足以下 並且給定要的對數k
inverse pair -> i < j , nums[i] > nums[j]
dp[i][對數] : 加入數字i時k=j時有多少種放法
[x x x x x] 6
看能插入哪裡 dp[6][j] += dp[5][j-5](插在頭) + dp[5][j-4](插在第二個)....
dp[i][j] += sum(dp[i-1][j-k]) for k = 0,....i-1 
這樣寫其實就能過但是n^3過得很免強 
可以再用數學來優化
dp[i][j] = dp[i-1][j-0] + dp[i-1][j-1] + ... dp[i-1][j-(i-1)];
dp[i][j-1] = dp[i-1][j-1] + dp[i-1][j-2] + ... dp[i-1][j-i];
dp[i][j] - dp[i][j-1] = dp[i-1][j] - dp[i-1][j-i];
dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-i];
*/
