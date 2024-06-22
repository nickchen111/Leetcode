/*
3192. Minimum Operations to Make Binary Array Elements Equal to One II
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        
        bool flag = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            if((nums[i] == 1 && flag == 0)|| (flag == 1 && nums[i] == 0)) continue;
            else {
                res += 1;
                if(flag) flag = 0;
                else flag = 1;
            }
        }
        
        return res;
    }
};

/*
可以任意選一個位置 然後翻轉包含他後面所有的數字 問最少需要翻幾次讓他全部變成1
*/
