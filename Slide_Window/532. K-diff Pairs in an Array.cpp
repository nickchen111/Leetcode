/*
532. K-diff Pairs in an Array
*/

// TC:O(nlgn+n) SC:O(1)
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        if(nums.size() < 2) return 0;
        sort(nums.begin(),nums.end());
        int res = 0;
        int j = 0;
        int i = 0;
        while(j < nums.size()){
            j = i+1;
            while(j < nums.size() && nums[j]-nums[i] < k) j++;
            if(j < nums.size() && nums[j]-nums[i] == k) res++;
            i++;
            while(i < nums.size() && nums[i] == nums[i-1]) i++;
        }
        return res;
    }
};


// 2/27
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        int j = 1;
        int i = 0;
        while(j < n){
            j = max(i+1, j);
            while(j < n && nums[j] - nums[i] < k) j++;
            
            if(j < n && nums[j] - nums[i] == k) res +=1;
            i++;
            while(i < n && nums[i] == nums[i-1]) i++;
        }

        return res;
    }
};
