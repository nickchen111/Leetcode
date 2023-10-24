/*
918. Maximum Sum Circular Subarray
*/

//這題超怪 不是很懂題目邏輯
//一般數組求出subarray最大or把中間最低的那一段去掉 的最大哪個大 -> 此即為circular存在的狀況最大值之一
//TC:O(n) SC:O(2*n)
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        

        int n = nums.size();
        //定義一個dp means  the maximum possible sum of a non-empty subarray of nums[0:i]
        vector<int> dp1(n);//for max
        vector<int> dp2(n);// for min
        dp1[0] = nums[0];
        dp2[0] =nums[0];
        int sumTotal = nums[0];
        int minSum = nums[0];
        int res = nums[0];
        for(int i = 1; i < n; i++){
            dp1[i] = max(dp1[i-1] + nums[i], nums[i]);
            dp2[i] = min(dp2[i-1]+nums[i], nums[i]);
            sumTotal +=nums[i];
            minSum = min(minSum, dp2[i]);
            res = max(res, dp1[i]);
        }
        if(sumTotal == minSum) return res;//nums數組全部都是負數的情況

        res = max(res, sumTotal-minSum);


        return res;
    }
};

//優化 TC:O(n) SC:O(1)
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        

        int n = nums.size();
        //定義一個dp means  the maximum possible sum of a non-empty subarray of nums[0:i]

        int MaxVal = nums[0];
        int MinVal =nums[0];
        int sumTotal = nums[0];
        int minSum = nums[0];
        int res = nums[0];
        for(int i = 1; i < n; i++){
            MaxVal = max(MaxVal + nums[i], nums[i]);
            MinVal = min(MinVal+nums[i], nums[i]);
            sumTotal +=nums[i];
            minSum = min(minSum, MinVal);
            res = max(res, MaxVal);
        }
        if(sumTotal == minSum) return res;//nums數組全部都是負數的情況

        res = max(res, sumTotal-minSum);


        return res;
    }
};

/*
circular 題型...想到index*2來跑兩次計算-> wrong
*/
