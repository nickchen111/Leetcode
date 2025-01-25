// TC:O(n) SC:O(1)
class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        int n = s.size();
        int cnt1 = 0, cnt0 = 0, ans = 0, i = 0;
        for(int j = 0; j < n; j++) {
            cnt1 += (s[j] == '1');
            cnt0 += (s[j] == '0');
            while(cnt1 > k && cnt0 > k) {
                cnt1 -= (s[i] == '1');
                cnt0 -= (s[i++] == '0');
            }
            ans += j - i + 1;
        }
        return ans;
    }
};
