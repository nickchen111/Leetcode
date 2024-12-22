/*
3397. Maximum Number of Distinct Elements After Operations
*/

//TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        int res = 1;
        for(int i = 0; i < n; i++) {
            if(i == 0) nums[i] = nums[i] - k;
            else {
                nums[i] = min(nums[i]+k, max(nums[i-1] + 1, nums[i] - k));
                res += (nums[i] != nums[i-1]);
            }
        }
        
        return res;
    }
};


// 
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int pre = INT_MIN;
        int res = 0;
        for(int i = 0; i < n; i++) {
            nums[i] = min(nums[i]+k, max(pre + 1, nums[i] - k));
            res += (nums[i] != pre);
            pre = nums[i];
            
        }
        
        return res;
    }
};
