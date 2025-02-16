// TC:O(n) SC:O(26)
class Solution {
public:
    bool hasSpecialSubstring(string s, int k) {
        int n = s.size();
        vector<int> cnt(26);
        unordered_set<int> set;
        int diff = 0, i = 0;
        for(int j = 0; j < n; j++) {
            cnt[s[j] - 'a'] += 1;
            if(cnt[s[j] - 'a'] == 1) {
                diff += 1;
                set.insert(s[j] - 'a');
            }
            if(j - i + 1 == k) {
                if(diff == 1) {
                    int ch = *set.begin();
                    if((i - 1 < 0 || s[i-1] - 'a' != ch) && (j + 1 >= n || s[j+1] - 'a' != ch)) return true;
                }
                cnt[s[i] - 'a'] -= 1;
                if(cnt[s[i] - 'a'] == 0) {
                    diff -= 1;
                    set.erase(s[i] - 'a');
                }
                i += 1;
            }
        }
        return false;
    }
};
