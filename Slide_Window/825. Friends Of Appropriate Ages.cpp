// TC:O(n + U) SC:O(U)
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int n = ages.size();
        vector<int> cnt(121);
        for(int a:ages) cnt[a] += 1;
        int ans = 0, age_y = 0, cnt_window = 0;
        for(int age_x = 0; age_x < 121; age_x++) {
            cnt_window += cnt[age_x];
            while(age_y *2 <= age_x + 14) {
                cnt_window -= cnt[age_y++]; 
            }
            if(cnt_window > 0) {
                ans += cnt[age_x] * cnt_window - cnt[age_x];
            }
        }
        return ans;
    }
};
