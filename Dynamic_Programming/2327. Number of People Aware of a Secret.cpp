/*
2327. Number of People Aware of a Secret
*/

// Diff TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        
        vector<LL> dp(n+1, 0);
        vector<LL> diff(n+1,0);
        diff[1] += 1;
        diff[2] -= 1;
       
        for(int i = 1; i <= n; i++){
            dp[i] = (dp[i-1] + diff[i] + M) %M;
            if(i+delay <= n) {
                diff[i+delay] += dp[i];
                diff[i+delay] %= M;
            }
            if(i+forget <= n) diff[i+forget] -= dp[i];
        }

        LL res = 0;
        for(int i = 1; i <= n; i++){
            if(i+forget > n) res = (res + dp[i]) % M;
        }
        

        return res;
    }
};


//DP TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        
        vector<LL> dp(n+1, 0);
        dp[1] = 1;
        LL res = 0;
        for(int i = 1; i <= n; i++){
            for(int j = i + delay; j < min(i + forget, n+1); j++){
                dp[j] = (dp[j] + dp[i]) %M;
            }
        }

        for(int i = 1; i <= n; i++){
            if(i+forget > n) res = (res + dp[i]) % M;
        }
        

        return res;
    }
};

/*
天數 會是下標
delay後代表某個人會守不住秘密開始大嘴巴 但他在forget天以後會忘記
問說第 n 天會有多少人知道秘密
當前知道秘密人數會跟delay 天 forget 天以前有關 -> DP
dp[n]代表第 n天 剛知道秘密的人數 
或者也可用差分數組來做 因為每次加入的區間都會是當天的+delay ~ i + forget之前 對這段進行差分

*/

