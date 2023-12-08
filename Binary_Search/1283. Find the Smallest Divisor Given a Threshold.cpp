/*
1283. Find the Smallest Divisor Given a Threshold
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int n = nums.size();
        int left = 1;
        int right = *max_element(nums.begin(),nums.end());
        while(left < right){
            int mid = left + (right - left)/2;
            if(solve(nums,mid) > threshold){
                left = mid + 1;
            }
            else right = mid;
        }

        return left;
    }
    int solve(vector<int>& nums, int mid){
        int sum = 0;
        for(auto num:nums){
            if(num % mid != 0){
                sum += (num/mid) + 1;
            }
            else sum += num/mid;
        }

        return sum;
    }
};
