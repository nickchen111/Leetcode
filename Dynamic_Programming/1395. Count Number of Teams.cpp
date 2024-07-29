/*
1395. Count Number of Teams
*/

// Array: 類似瞻前顧後 TC:O(n^2) SC:O(1)
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
        rating.insert(rating.begin(), 0);
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(4, vector<int>(2,0))); // 走到i 時 可以有的上升or下降長度為j 的組數有多少個
        dp[1][1][1] = 1;
        dp[1][1][0] = 1;

        dp[2][2][0] = (rating[2] > rating[1] ? 1 : 0); // 0 是上升
        dp[2][2][1] = (rating[2] < rating[1] ? 1 : 0);
        dp[2][1][0] = 1;
        dp[2][1][1] = 1;
        int res = 0;
        for(int i = 3; i <= n; i++){
            dp[i][1][1] = 1;
            dp[i][1][0] = 1;
            for(int j = i-1; j >= 1; j--){
                if(rating[i] > rating[j]){
                    dp[i][3][0] += dp[j][2][0];
                    dp[i][2][0] += dp[j][1][0];
                }
                else {
                    dp[i][3][1] += dp[j][2][1];
                    dp[i][2][1] += dp[j][1][1];
                }
            }

            res += dp[i][3][0];
            res += dp[i][3][1];
        }

        return res;
    }
};
