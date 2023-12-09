/*
2958. Length of Longest Subarray With at Most K Frequency
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        unordered_map<int,int> map; // val -> freq;
        int res = 1;
        int n = nums.size();
        int j = 0;
        for(int i = 0; i < n; i++){
            while(j < n && map[nums[j]] < k){
                map[nums[j]] += 1;
                res = max(res, j - i + 1);
                j++;
            }
            
            map[nums[i]] -= 1;
        }
        
        return res;
    }
};

/*
每個字的頻率小於或者等於k就代表是好的subarry 問最長長度可以是多少
*/
