/*
27. Remove Element
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        int fast = 0;
        while(fast < nums.size()){
            if(nums[fast] != val){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        //返回長度 這裡是先給slow賦值在++ 所以不用＋1
        return slow;
    }
};

/*
解題思路 
用雙指針 fast 指導跟val 不一樣的值 就將slow等於fast 
這個解法更直觀
*/
