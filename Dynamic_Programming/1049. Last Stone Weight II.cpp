/*
1049. Last Stone Weight II
*/

// 遞歸 + 遞推
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int total = reduce(stones.begin(), stones.end(), 0);
        // 另一種思維 TC:O(n*total/2) SC:O(total/2)
        auto helper = [&](int sum) -> int {
            vector<bool> dp(sum+1);
            dp[0] = 1;
            for(int i = 0; i < n; i++) {
                for(int j = sum; j >= stones[i]; j--) {
                    if(dp[j-stones[i]]) {
                        dp[j] = 1;
                    }
                }
            }

            return res;
        };
        int near = helper(total/2);
        return total - near - near; // 也就是 大的最接近的累加和 - 較小一點盡量接近total/2的累加和

        /*
        空間優化 TC:O(n*total) SC:O(total)
        int offset = total;
        vector<bool> dp(2*total+1);
        dp[offset] = true;
        for(int i = 0; i < n; i++) {
            vector<bool> dp_tmp(2*total+1);
            for(int j = total; j >= -total; j--) {
                if(j + offset + stones[i] <= 2*total && dp[j + offset]) {
                    dp_tmp[j + offset + stones[i]] = true;
                }
                if(j + offset - stones[i] >= 0 && dp[j + offset]) {
                    dp_tmp[j + offset - stones[i]] = true;
                }
            }
            dp = dp_tmp;
        }
        for(int j = total; j <= 2*total; j++) {
            if(dp[j]) return j - offset;
        }

        return -1;
        */
        /*
        遞推 TC:O(n*total) SC:O(n*total)
        vector<vector<bool>> dp(n+1, vector<bool>(2*total+1, 0));
        dp[0][offset] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = total; j >= -total; j--) {
                if(j + stones[i] + offset <= 2*total && dp[i][j+offset]) {
                    dp[i+1][j + stones[i] + offset] = true;
                }
                if(j - stones[i] + offset >= 0 && dp[i][j+offset]) {
                    dp[i+1][j - stones[i] + offset] = true;
                }
            }
        }

        for(int j = total; j <= 2*total; j++) {
            if(dp[j]) return j - offset;
        }
        
        return -1;
        */
        /*
        遞歸 TC:O(n*total) SC:O(n*total)
        vector<vector<int>> memo(n, vector<int>(2*total+1,-1));
        function<int(int,int)> dfs = [&](int i, int sum) -> int {
            if(i < 0) return sum < 0 ? INT_MAX : sum;
            if(memo[i][sum+offset] != -1) return memo[i][sum+offset];

            return memo[i][sum+offset] = min(dfs(i-1, sum + stones[i]), dfs(i-1, sum - stones[i]));
        };

        return dfs(n-1, 0);
        */
    }
};
