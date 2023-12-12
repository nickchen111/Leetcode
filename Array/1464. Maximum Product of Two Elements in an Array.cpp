/*
1464. Maximum Product of Two Elements in an Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int first_element = nums[0];
        int second_element = 0;

        for(int i = 1; i < n; i++){
            if(nums[i] >= first_element){
                second_element = first_element;
                first_element = nums[i];
            }
            else if(nums[i] > second_element){
                second_element = nums[i];
            }
        }

        return (first_element - 1) * (second_element - 1);
    }
};

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        return (nums[n-1]-1)*(nums[n-2]-1);
    }
};
