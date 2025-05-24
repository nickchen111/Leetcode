// TC:O(4 * n -> n) SC:O(n)
class Solution {
public:
    int maxSubstrings(string s) {
        /*
        找到至少長度4 且開頭結束為同一個元素的最長字串 類似滑窗 因為題目只有小寫字母所以可以枚舉
        但是要確保這些字串不能重疊
        想到劃分DP 用一個dp[i] 走到i的時候可以達到的最多劃分個數是多少
        每個點應該只需要往前訪問到可以構成4長度的即可 然後判斷組成最長長度是多少? 因為越往前肯定越小沒必要 長度只有四那我就可以窮舉
        */
        int ans = 0;
        int n = s.size();
        vector<int> dp(n);
        vector<vector<int>> pos(26);
        pos[s[0] - 'a'].emplace_back(0);
        for (int i = 1; i < n; i++) {
            // 代表有字母
            if (!pos[s[i] - 'a'].empty()) {
                for (int j = pos[s[i] - 'a'].size() - 1; j >= 0; j--) {
                    if (i - pos[s[i] - 'a'][j] + 1 >= 4) {
                        dp[i] = max(dp[i - 1], (pos[s[i] - 'a'][j] - 1 >= 0 ? dp[pos[s[i] - 'a'][j] - 1] : 0) + 1);
                        break;
                    }
                }
            }
            dp[i] = max(dp[i], dp[i-1]);
            ans = max(ans, dp[i]);
            pos[s[i] - 'a'].emplace_back(i);
        }
        return ans;
    }
};
