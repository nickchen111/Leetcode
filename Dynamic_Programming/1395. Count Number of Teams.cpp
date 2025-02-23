/*
1395. Count Number of Teams
*/

// Array: 前後綴分解 類似瞻前顧後 TC:O(n^2) SC:O(1)
class Solution {
public:
   int numTeams(vector<int>& rating) {
        int res = 0;
        for (auto i = 1; i < rating.size() - 1; ++i) {
            int less[2] = {}, greater[2] = {};
            for (auto j = 0; j < rating.size(); ++j) {
                if (rating[i] < rating[j])
                    ++less[j > i];
                if (rating[i] > rating[j])
                    ++greater[j > i];
            }
            res += less[0] * greater[1] + greater[0] * less[1];
        }
        return res;
    }
};

// DP TC:O(n^2) SC:O(n)
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        vector dp(n+1, vector<vector<int>>(4, vector<int>(2, 0)));
        int ans = 0;
        for(int i = 0; i < n; i++) {
            dp[i+1][1][1] = 1;
            dp[i+1][1][0] = 1;
            for(int j = 0; j < i; j++) {
                if(rating[i] > rating[j]) {
                    dp[i+1][3][0] += dp[j+1][2][0];
                    dp[i+1][2][0] += dp[j+1][1][0];
                }
                else {
                    dp[i+1][3][1] += dp[j+1][2][1];
                    dp[i+1][2][1] += dp[j+1][1][1];
                }
            }
            ans += dp[i+1][3][0];
            ans += dp[i+1][3][1];
        }
        return ans;
    }
};
