// TC:O(26 * n ^ 2) SC:O(26)
class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            vector<int> cnt(26);
            
            for (int j = i; j < n; j++) {
                cnt[s[j] - 'a'] += 1;
                // 確定頻率是否都相同
                int freq = -1;
                for (int k = 0; k < 26; k++) {
                    if (cnt[k]) {
                        if (freq == -1) freq = cnt[k];
                        else if (freq != cnt[k]) {
                            freq = -1;
                            break;
                        }
                    }
                }
                if (freq != -1) ans = max(ans, j - i + 1);
            }
        }

        return ans;
    }
};
