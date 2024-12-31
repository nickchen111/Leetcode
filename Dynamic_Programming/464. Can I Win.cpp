/*
464. Can I Win
*/

// TC:O(n * 2^n) SC:O(2^n) 遞歸快很多 因為很多狀態不必走到 
class Solution {
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (desiredTotal == 0) return true;
        if ((maxChoosableInteger * (maxChoosableInteger + 1)) / 2 < desiredTotal) return false;

        vector<int> dp(1 << maxChoosableInteger, -1);
        vector<int> sum(1 << maxChoosableInteger,0);
        for(int i = 0; i < (1 << maxChoosableInteger); i++) {
            for(int j = 0; j < maxChoosableInteger; j++) {
                if(((i >> j) & 1)) sum[i] += (j + 1);
            }
        } 

        for (int mask = (1 << maxChoosableInteger) - 1; mask >= 0; --mask) {
            int currentTotal = sum[mask];
            if (currentTotal >= desiredTotal) {
                dp[mask] = false;
                continue;
            }

            dp[mask] = false;
            for (int i = 0; i < maxChoosableInteger; ++i) {
                if ((mask & (1 << i)) == 0) { 
                    if (!dp[mask | (1 << i)]) {
                        dp[mask] = true;
                        break;
                    }
                }
            }
        }

        return dp[0];
        /*
        遞歸 TC:O(n * 2^n) SC:O(2^n)
        vector<int> memo(1 << maxChoosableInteger, -1);

        auto dfs = [&](auto&& dfs, int mask, int total) -> bool {
            if (total >= desiredTotal) return false;
            if (memo[mask] != -1) return memo[mask];

            for (int i = 0; i < maxChoosableInteger; i++) {
                if ((mask & (1 << i)) == 0 && !dfs(dfs, mask | (1 << i), total + i + 1)) {
                    return memo[mask] = true;
                }
            }
            return memo[mask] = false;
        };

        return dfs(dfs, 0, 0);
        */
    }
};


/*
在選擇了state狀態下是否能贏 state 的總和先計算出來 然後根據選擇的數字判斷目前是讓誰選
*/
