/*
2915. Length of the Longest Subsequence That Sums to Target
*/

// TC:O(target*n) SC:O(n*target)
class Solution {
    int dp[1002][1002];
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();

        for(int i = 0; i < n; i++){
            for(int j = 0; j <=target; j++){
                dp[i][j] = INT_MIN;
            }
        }
        dp[0][0] = 0;

        for(int i = 0; i < n; i++){
            dp[i][nums[i]] = 1;
        }

        for(int i = 1; i < n; i++){//遍歷物品
            for(int ta = 0; ta <= target; ta++){//遍歷容量
                dp[i][ta] = dp[i-1][ta];
                if(ta - nums[i] >= 0)
                    dp[i][ta] = max(dp[i][ta], dp[i-1][ta-nums[i]] + 1);
            }
        }

        int res = -1;
        for(int i = 0; i < n; i++){
            res = max(res, dp[i][target]);
        }

        return res;
    }
};

/*
一個數組中的數字 其subsequence可以加總到target的最長長度
會想要盡量先挑小的疊加上去 如果超過了將最小的丟掉
中間想到3sum , slide window 滑窗適用求subarray 3sum不曉得確切長度也沒辦法照做
dp[i][j]截止到i為止能夠累加到j的最大長度
i可以是選or不選
dp[i][j] = dp[i-1][j] 不選
dp[i][j] = max(dp[i][j], dp[i-1][j-?] + 1);
此題跟494, 416很像 494在求 有多少種方法可以得到此target  416在求是否可以加總到target
*/
