/*
2419. Longest Subarray With Maximum Bitwise AND
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        int maxVal = *max_element(nums.begin(), nums.end());

        for(int i = 0; i < n; i++){
            if(nums[i] == maxVal){
                int j = i;
                while(j < n && nums[j] == maxVal) j++;
                res = max(res, j-i);
                i = j;
            }
        }

        return res;
    }
};

/*
AND 
101 & 101 = 111
*/
