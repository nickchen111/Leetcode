/*
152. Maximum Product Subarray
*/

//TC:O(n) SC:O(2*n)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        //用dp
        vector<int> dp1(n);//求最大值
        vector<int> dp2(n);//求最小值   
        dp1[0] = nums[0];
        dp2[0] = nums[0];
        int res = nums[0];

        for(int i = 1; i < n; i++){
            dp1[i] = max(dp1[i-1]*nums[i],max(dp2[i-1]*nums[i], nums[i]));
            dp2[i] = min(dp1[i-1]*nums[i],min(dp2[i-1]*nums[i], nums[i]));
            res = max(res, dp1[i]);
        }

        return res;
    }
};
/*
1. presum? ->一樣遇到正負數問題 很難說最小的跟最大的之間就可以求出答案
2. slide window? -> 負數情況難判定 不太好界定何時該縮小窗口
3. dp
subarray 做法大概率就是固定右邊邊界探索左邊

xxixxxj 
*/
