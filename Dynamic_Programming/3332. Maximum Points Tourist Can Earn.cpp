/*
3332. Maximum Points Tourist Can Earn
*/

// TC:O(k*n^2) SC:O(n)
class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<int> dp(n);
        for(int j = 0; j < n; j++) {
            dp[j] = stayScore[0][j];
            for(int t = 0; t < n; t++) {
                if(j != t)
                    dp[j] = max(dp[j], travelScore[t][j]);
            }
        }
        
        for(int i = 1; i < k; i++) {
            auto dp_tmp = dp;
            for(int j = 0; j < n; j++) {
                for(int t = 0; t < n; t++) {
                    if(j == t) {
                        dp[j] = max(dp[j], dp_tmp[t] + stayScore[i][j]);
                    }
                    else {
                        dp[j] = max(dp[j], dp_tmp[t] + travelScore[t][j]);
                    }
                }
            }
        }
        int res = 0;
        for(int j = 0; j < n; j++) {
            res = max(res, dp[j]);
        }
        
        return res;
    }
};


/*
可以走k天 每天可以做的選項是選擇從某座城市跨到某座城市，或者待到那座城市獲取分數
問說k天後可以獲得的最高分
dp[i][j] : 第i天後從第j座城市可以獲得的最高分數並且我是選擇留在原地 或者從其他城市轉移過來
2
1
[[1,1]]
[[0,1],[6,0]]
*/
