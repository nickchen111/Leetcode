/*
81. Search in Rotated Sorted Array II
*/

// TC:O(lgn) SC:O(1)
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        while(nums.size() > 1 && nums.back() == nums[0]){
            nums.pop_back();
        }

        int left = 0;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target) return true;
            if(target >= nums[0] == nums[mid] >= nums[0]){
                if(nums[mid] < target){
                    left = mid+1;
                }
                else right = mid-1;
            }
            //不同邊的話只要關注target在哪
            else if(target>=nums[0]){
                right = mid-1;
            }
            else left = mid+1;
        }

        if(left == right && nums[left] == target) return true;
        else return false;
    }
};

/*
此題為33題的變形
如果允許重複數字的話
在這種情況下會有問題
1 1 1 2 2 3 4 5 6 0 0 1 1 if target = 1
  M                   T
會判斷失誤 那麼只要將尾巴的重複像去掉就好哩
*/
