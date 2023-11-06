/*
189. Rotate Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k%nums.size();
        int n = nums.size();
        if(k == 0) return;
        //先將整個araay reverse
        int left=0;
        int right = n-1;
        while(left < right){
            swap(nums[left],nums[right]);
            left++;right--;
        }
        //再將前k個單獨翻轉
        left = 0;
        right = k-1;
        while(left < right){
            swap(nums[left],nums[right]);
            left++;right--;
        }

        //最後轉後面幾個
        left = k;
        right = n-1;
        while(left < right){
            swap(nums[left],nums[right]);
            left++;right--;
        }
    }
};
