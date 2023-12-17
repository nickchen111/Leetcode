/*
1509. Minimum Difference Between Largest and Smallest Value in Three Moves
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if(n <= 3) return 0;


        sort(nums.begin(), nums.end());
        int k = 3;
        int diff = nums.back() - nums[k];
        for(int i = 1; i <= k; i++){
            diff = min(diff, nums[n-1-i] - nums[k-i]);
        }

        return diff;
    }
};

/*
最多可以換任意數字三次
求出數組內最小數字跟最大數字之間差的最小值
[1,5,0,10,14] -> [0 1 5 10 14]-> 0 10 14
[0 1 5 13 14] -> 兩種換法 
[5,3,2,4] -> [2 3 4 5]
[3 100 300 400 500 700 1000]
想換的可能性為 前三後三取三個 這三個數字對所有人的影響最大
*/
