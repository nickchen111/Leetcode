/*
2576. Find the Maximum Number of Marked Indices
*/

// TC:O(n + nlgn) SC:O(1)
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(nums.begin(), nums.end());
       
        int n = nums.size();
        int j = n/2;
        int count = 0;
        for(int i = 0; i < n/2; i++){
            while(j < n && nums[i]*2 > nums[j]){
                j++;
            }
            if(j < n){
                count += 2;
                j++;
            }
        }

        return count;
    }
};

/*
將數組內所有滿足以下條件的點都mark起來
2*nums[i] <= nums[j]
[3,5,2,4] -> [2 3 4 5] -> [2] [ 3 4 5]  1,3
[9,2,5,4] -> [2 4 5 9]
[9, 10, 10, 14, 15, 16, 17, 17, 24, 28, 29, 31, 32, 40, 42, 48, 51, 55, 64, 68, 71, 83, 98, 99, 99, 100]
3 6 7 10  各自不能跟各自裡面的人配對 
這題要先想到最多對的狀況肯定是n/2對
所以最貪心的做法就是找二分線切割兩等份出來 左邊對左邊一路對過去 不可能存在一對漏掉的是自己那一半可以配對的 如果自己一半都可以配對了 那麽在另一半就更可以了
*/
