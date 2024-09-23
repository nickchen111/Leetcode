/*
2420. Find All Good Indices
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> prefix(n,1);
        vector<int> suffix(n,1);
        prefix[0] = 0;
        prefix[1] = 1;
        for(int i = 2; i < n; i++){
            if(nums[i-1] <= nums[i-2]){
                prefix[i] = prefix[i-1] + 1;
            }
        }

        suffix[n-1] = 0;
        suffix[n-2] = 1;
        for(int i = n-3; i >= 0; i--){
            if(nums[i+1] <= nums[i+2]){
                suffix[i] = suffix[i+1] + 1;
            }
        }

        vector<int> res;

        for(int i = k; i < n-k; i++){
            if(prefix[i] >= k && suffix[i] >= k){
                res.push_back(i);
            }
        }

        return res;
    }
};
