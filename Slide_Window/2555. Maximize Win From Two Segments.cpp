// TC:O(n) SC:O(n)
class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        vector<int> dp(n + 1, 0);
        int ans = 0;
        int i = 0;

        for (int j = 0; j < n; j++) {
            while (prizePositions[j] - prizePositions[i] > k) {
                i++;
            }
            dp[j + 1] = max(dp[j], j - i + 1);
        }

        i = 0;
        for (int j = 0; j < n; j++) {
            while (prizePositions[j] - prizePositions[i] > k) {
                i++;
            }
            ans = max(ans, j - i + 1 + dp[i]);
        }

        return ans;
    }
};
