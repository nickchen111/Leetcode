/*
2905. Find Indices With Index and Value Difference II
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        int n = nums.size();
        pair<int,int> pre_min = {INT_MAX,-1}; pair<int,int> pre_max = {INT_MIN,-1};
        for(int i = indexDifference; i<n; i++){
            int j = i-indexDifference;
            pre_min = (pre_min.first > nums[j]) ? make_pair(nums[j],j):pre_min;
            pre_max = (pre_max.first < nums[j] )? make_pair(nums[j],j):pre_max;
            
            //check nums[i] have the 
            if(abs(nums[i]-pre_min.first) >= valueDifference) return {pre_min.second,i};
            else if(abs(nums[i]-pre_max.first) >= valueDifference) return {pre_max.second,i};
        }
        return {-1,-1};
    }
};

// [3 4 6 1 3 2 4 5 6 7 8]
// val: 4
// index: 2

