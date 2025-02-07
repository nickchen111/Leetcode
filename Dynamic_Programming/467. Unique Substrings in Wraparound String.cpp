// TC:O(n) SC:O(1)
class Solution {
public:
    int findSubstringInWraproundString(string s) {
        int n = s.size(), ans = 0, i = n-1;
        vector<int> cnt(26); // 每個字母開始的長度最大值
        while(i >= 0) {
            int start = i;
            while(i - 1 >= 0 && ((((s[i] - 'a') - 1) % 26 + 26) % 26) == ((s[i-1] - 'a') % 26)) {
                cnt[s[i] - 'a'] = max(cnt[s[i] - 'a'], start - i + 1);
                i -= 1;
            }
            cnt[s[start] - 'a'] = max(cnt[s[start] - 'a'], 1);
            cnt[s[i] - 'a'] = max(cnt[s[i] - 'a'], start - i + 1);
            i -= 1;
        }

        for(int i = 0; i < 26; i++) {
            ans += cnt[i];
        }
        return ans;
    }
};
