/*
3209. Number of Subarrays With AND Value of K
*/

// TC:O(nlgU) SC:O(1) Three Pointers
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long res = 0;
        int left = 0;
        int right = 0;
        for(int i = 0; i < n; i++){
            for(int j = i-1; j >= 0; j--){
                if((nums[j]&nums[i]) == nums[j]) break;
                nums[j] &= nums[i];
            }
            
            while(left <= i && nums[left] < k) left++;
            while(right <= i && nums[right] <= k) right++;

            res += (long long)(right - left);
        }

        return res;
    }
};

// TC:O(nlgU + n*lgn) SC:O(1) Binary Search
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long res = 0;
        for(int i = 0; i < n; i++){
            for(int j = i-1; j >= 0; j--){
                if((nums[j]&nums[i]) == nums[j]) break;
                nums[j] &= nums[i];
            }
            auto right = upper_bound(nums.begin(), nums.begin() + i+1, k);
            auto left =  lower_bound(nums.begin(), nums.begin() + i+1, k);
            res += (long long)(right - left);
        }

        return res;
    }
};
