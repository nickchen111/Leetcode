// TC:O(n * m + n ^ 2 + m ^ 2) SC:O(n ^ 2 + m ^ 2)
class Solution {
public:
    int longestPalindrome(string s, string t) {
        /*
        reverse其中一個字串 題目變成問說 兩個字串最長有多少個一樣?!
        單個字串好求 單獨求最長回文串即可
        整個邏輯是枚舉回文串 然後往後去找他們的最長公共子串
        */
        auto cal = [] (string s, string t) -> int {
            int n = s.size(), m = t.size();
            // int ans = 1;
            // 首先計算每個字串LCS狀況
            reverse(t.begin(), t.end()); // reverse後計算兩個區間的LCS 最長公共子串
            vector lcs(n + 1, vector<int>(m + 1));
            vector<int> mx(n + 1); // 從某個點出發的string s 可以匹配到多少個LCS
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(s[i] == t[j]) {
                        lcs[i+1][j+1] = lcs[i][j] + 1;
                        // ans = max(ans, lcs[i][j] * 2);
                        mx[i] = max(mx[i], lcs[i+1][j+1]);
                    }
                }
                // mx[i] = ranges::max(lcs[i]);
            }
            int ans = ranges::max(mx) * 2;
            for (int i = 0; i < 2 * n - 1; i++) {
                int l = i / 2, r = (i + 1) / 2;
                while(l >= 0 && r < n && s[l] == s[r]) {
                    l -= 1;
                    r += 1;
                }
                if(l + 1 <= r - 1) {
                    ans = max(ans, (l < 0 ? 0 : mx[l] * 2) + (r - l - 1));
                }
            }
            return ans;
        };
        string rs = s, rt = t;
        reverse(rs.begin(), rs.end());
        reverse(rt.begin(), rt.end());
        return max(cal(s, t), cal(rt, rs));
        
    }
};
