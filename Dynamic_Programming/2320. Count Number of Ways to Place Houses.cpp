/*
2320. Count Number of Ways to Place Houses
*/


// 優化空間TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countHousePlacements(int n) {
        LL build = 1; LL nobuild = 1;
        for(int i = 2; i<=n; i++){
            int build_tmp = build, nobuild_tmp = nobuild;
            build = nobuild_tmp%M;
            nobuild = (build_tmp + nobuild_tmp)%M;
        }
        LL res = ((build + nobuild)*(build + nobuild))%M;

        return res;
    }
};

// 
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    int dp[10002][2];
public:
    int countHousePlacements(int n) {
        dp[0][0] = 1; dp[0][1] = 0;
        for(int i = 1; i<=n; i++){
            dp[i][0] = (dp[i-1][0] + dp[i-1][1])%M;
            dp[i][1] = dp[i-1][0];
        }
        LL res = ((dp[n][1] + dp[n][0])%M*(dp[n][1] + dp[n][0]))%M;

        return res;
    }
};
