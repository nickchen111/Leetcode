/*
41. First Missing Positive
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        for(int i = 1; i <= n; i++){
            while(nums[i] != i && nums[i] > 0 && nums[i] < nums.size() && nums[i] != nums[nums[i]]){
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i <= n; i++){
            if(nums[i] != i) return i;
        }

        return nums.size();


    }
};

/*
找最小的正整數是沒有在數組內的 並且要在O(n)時間找出 以及 O(1)額外空間
*/
