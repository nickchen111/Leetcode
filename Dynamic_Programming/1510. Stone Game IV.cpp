/*
1510. Stone Game IV
*/

// TC:O(n^2) SC:O(n) DP寫法
class Solution {
    int dp[100005];
public:
    bool winnerSquareGame(int n) {
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j*j <= i; j++){
                if(dp[i-j*j] == 0){
                    dp[i] = 1;
                    break;
                }
            }
        }

        return dp[n];
    }
};

// top down 
class Solution {
    int dp[100005];
public:
    bool winnerSquareGame(int n) {
        for(int i = 0; i <= n; i++){
            dp[i] = -1;
        }
        return solve(n);
    }

    bool solve(int n){
        if(dp[n] != -1) return dp[n];

        for(int i = 1; i*i <= n; i++){
            //對手輸
            if(solve(n-i*i) == false){
                dp[n] = 1;
                return true;
            }
        }
        
        dp[n] = false;
        return false;
    }
};

/*
每次可以移除 某個數字的平方數量的石頭 誰可以移到石頭變成沒有就贏了
必輸局面 : 最終都是如果對方遇到0那對方就是輸掉了
*/
