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
                int minR = nums[i] - k, maxR = nums[i] + k;
                if(nums[i-1] < minR) {
                    nums[i] = minR;
                    res += 1;
                }
                else if(nums[i-1] == maxR) {
                    nums[i] = nums[i-1];
                }
                else {
                    nums[i] = nums[i-1] + 1;
                    res += 1;
                }
            }
        }
        
        return res;
    }
};
