/*
3191. Minimum Operations to Make Binary Array Elements Equal to One I
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        bool flag = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] == 1) continue;
            else {
                if(i + 2 < n){
                    res += 1;
                    
                    nums[i] = 1;
                    if(nums[i+1] == 1) nums[i+1] = 0;
                    else nums[i+1] = 1;
                    
                    if(nums[i+2] == 1) nums[i+2] = 0;
                    else nums[i+2] = 1;
                }
                else return -1;
            }
        }
        
        return res;
    }
};

/*
可以任選三個翻轉 問最少要翻幾次 全部變1 or 做不到

*/
