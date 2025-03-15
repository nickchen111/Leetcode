// 暴力 TC:O(n^3) SC:O(1)
class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int n = digits.size();
        vector<int> cnt(10, 0);
        for(int i = 0; i < n; i++) {
            cnt[digits[i]]++;
        }
        int ans = 0;
        for(int last = 0; last <= 8; last += 2) {
            if(cnt[last] == 0) continue;
            cnt[last]--;
            for(int hundreds = 1; hundreds <= 9; hundreds++) {
                if(cnt[hundreds] == 0) continue;
                cnt[hundreds]--;
                for(int tens = 0; tens <= 9; tens++) {
                    if(cnt[tens] == 0) continue;
                    ans++;
                }
                cnt[hundreds]++;
            }
            cnt[last]++;
        }
        
        return ans;
    }
};
