// TC:O(n * lgU) U 為數字最大值 SC:O(M) M 為數字累加結果大概在9*5範圍內
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size(), ans = -1;
        unordered_map<int, int> mx,smx, freq;
        for(int i = 0; i < n; i++) {
            int cur = 0,tmp = nums[i];
            while(tmp) {
                cur += tmp % 10;
                tmp /= 10;
            }
            if(nums[i] > mx[cur]) {
                smx[cur] = mx[cur];
                mx[cur] = nums[i];
            }
            else if(nums[i] > smx[cur]) smx[cur] = nums[i];
            freq[cur] += 1;
            if(freq[cur] > 1) {
                ans = max(ans, mx[cur] + smx[cur]);
            }
        }
        return ans;
    }
};
