// TC:O(n^2) SC:O(1) -> TC:O(n) SC:O(n)
class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        vector<bool> suffix(n);
        suffix.back() = true;
        for(int i = n-2; i >= 0; i--) {
            if(nums[i] <= nums[i+1]) suffix[i] = true;
            else break;
        }
        if(suffix[0]) return true;
        bool prefix = true;
        int i = 0;
        while(prefix && i+1 < n) {
            // cout << "ok";
            if(prefix && suffix[i+1] && nums.back() <= nums[0]) return true;
            i += 1;
            prefix = prefix && nums[i] >= nums[i-1];  
        }
        // for(int i = 0; i < n; i++) {
        //     bool flag = true;
        //     for(int j = i; j < n + i - 1; j++) {
        //         if(nums[j % n] > nums[(j+1) % n]) {
        //             flag = false;
        //             break;
        //         }
        //     }
        //     if(flag) return true;
        // }
        return false;
    }
};
