// TC:O(n^2) SC:O(n)
class Solution {
public:
    int deleteString(string s) {
        int n = s.size();
        /*
        最長公共前綴作法
        vector lcp(n+1, vector<int>(n+1, 0)); // 最長公共前綴 針對每個點出發的比較
        for(int i = n - 1; i >= 0; i--) {
            for(int j = n-1; j > i; j--) {
                if(s[i] == s[j]) lcp[i][j] = lcp[i+1][j+1] + 1;
            }
        }
        vector<int> dp(n);
        for(int i = n - 1; i >= 0; i--) {
            for(int len = 1; i + len * 2 <= n; len++) {
                if(lcp[i][i + len] >= len) dp[i] = max(dp[i], dp[i+len]);
            }
            ++dp[i];
        }
        return dp[0];
        */

        // KMP
        vector<int> dp(n);
        vector<int> lps(n);
        auto KMP = [&](int base, int len) -> void {
            lps[0] = 0;
            for(int i = 1; i < len; i++) {
                int j = lps[i-1];
                while(j && s[i + base] != s[j + base]) j = lps[j-1];
                lps[i] = j + (s[i + base] == s[j + base]);
            }
        };
        for(int i = n - 1; i >= 0; i--) {
            int l = n - i;
            KMP(i, l);
            for(int j = 1; j < l; j+=2) {
                if(lps[j] * 2 == j + 1) dp[i] = max(dp[i], dp[i + lps[j]]);
            }
            ++dp[i];
        }
        return dp[0];
    }
};
