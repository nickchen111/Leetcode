/*
31. Next Permutation
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //後面的數字往後看 看有沒有比他大的數字 如果有就換位置 然後換過去的數字再從那裡出發往後換
        int n = nums.size();
        
        int i=n-1;
        while(i-1>=0 && nums[i-1] >=nums[i]){
            i--;
        }
        if(i == 0) {
            sort(nums.begin(),nums.end());
            return;
        }

        i--;//才會是要替換的位置
        int j = n-1;//找要跟誰換
        while(nums[j] <= nums[i]) j--;
        swap(nums[i],nums[j]);

        sort(nums.begin()+i+1,nums.end());
        return;
    }
};

