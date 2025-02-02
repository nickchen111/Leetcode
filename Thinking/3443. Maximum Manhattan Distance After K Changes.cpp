// TC:O(n) SC:O(1)
class Solution {
public:
    int maxDistance(string s, int k) {
        // 要是NE or NW or SE or SW 就會是可以走的
        int n = s.size(), sum0 = 0,sum1 = 0, sum2 = 0, sum3 = 0, cnt0 = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            if(s[j] == 'S' || s[j] == 'E') cnt0 += 1;
            if(s[j] == 'S' || s[j] == 'W') cnt1 += 1;
            if(s[j] == 'N' || s[j] == 'W') cnt2 += 1;
            if(s[j] == 'N' || s[j] == 'E') cnt3 += 1;
            sum0 += 1, sum1 += 1, sum2 += 1, sum3 += 1;
            while(cnt0 > k) {
                sum0 -= 2;
                cnt0 -= 1;
            }
            while(cnt1 > k) {
                sum1-= 2;
                cnt1 -= 1;
            }
            while(cnt2 > k) {
                sum2 -= 2;
                cnt2 -= 1;
            }
            while(cnt3 > k) {
                sum3 -= 2;
                cnt3 -= 1;
            }
            ans = max({ans, sum0, sum1, sum2, sum3});
        }
        return ans;
    }
};
