/*
1824. Minimum Sideway Jumps
*/

// TC:O(3*n) SC:O(3*n)
class Solution {
  int dp[500004][4];
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size()-1;
        dp[0][1] = dp[0][3] = 1;
        for(int i = 1; i <= n; i++){
            int obs = obstacles[i];
            int minVal = INT_MAX;
            for(int j = 1; j <=3; j++){
                if(j == obs){
                    dp[i][j] = INT_MAX;
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
                minVal = min(minVal, dp[i][j]);
            }

            for(int j = 1; j <= 3; j++){
              if(j != obs && dp[i][j] != minVal){
                  dp[i][j] = minVal + 1;
              }
            }
        }       
        int res = INT_MAX;
        for(int j = 1; j <= 3; j++){
            res = min(res, dp[n-1][j]);
        }

        return res;
    }
};

/*
此題題意是有三個賽道 一隻青蛙想跳到終點最少需要切換幾次賽道 中間會有障礙物
並且起點終點皆不會有障礙物
現在的狀態會跟前面一次狀態有關 基本型I 的DP題
*/
