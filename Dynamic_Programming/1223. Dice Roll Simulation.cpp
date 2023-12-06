/*
1223. Dice Roll Simulation
*/

// T:O(6*n*k*6*k) SC:O(6*n*k)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        auto dp = vector<vector<vector<int>>>(n, vector<vector<int>>(6,vector<int>(16,0)));
        for(int j = 0; j < 6; j++){
            dp[0][j][1] = 1;
        }

        for(int i = 1; i < n; i++){
            for(int j = 0; j < 6; j++){
                for(int k =1; k <= rollMax[j]; k++){
                    if(k > 1){
                        dp[i][j][k] = dp[i-1][j][k-1];
                    }
                    else {
                        for(int jj = 0; jj < 6; jj++){
                            if(j == jj) continue;//如果只投出一次不會有 dp[i][相同數字][1~max]的繼承過來
                            for(int kk = 1; kk <= rollMax[jj]; kk++){
                                dp[i][j][k] += dp[i-1][jj][kk];
                                dp[i][j][k]%=M;
                            }
                        }
                    }
                }
            }
        }
        int res = 0;
        for(int j = 0; j < 6; j++){
            for(int k = 1; k <= rollMax[j]; k++){
                res += dp[n-1][j][k];
                res%=M;
            }
        }

        return res;

    }
};

/*
此題給你一串數組說明1-6不能投出超過這麼多連續的次數 有幾種情況是合法的
每種情況有幾種可能都是取決於上一輪狀態  
dp[i] 第幾輪 [j] 投到哪個數字 [k] 此數字出現幾次
*/
