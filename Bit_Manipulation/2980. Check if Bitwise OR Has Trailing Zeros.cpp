/*
2980. Check if Bitwise OR Has Trailing Zeros
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int count = 0;
        for(int i = 0; i < nums.size(); i++){
            int cur = nums[i];
            if((cur & 1) == 0) count++;
            if(count >= 2) return true;
            
        }
        return false;
    }
};

/*
檢查OR運算 任意兩個元素是否會有trailing zero
OR:
1 | 0 -> 1
1 | 1 -> 1
0 | 0 -> 0 兩個都要是0
*/
