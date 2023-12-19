/*
2919. Minimum Increment Operations to Make Array Beautiful
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<long long> dp;
    int n;
public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        n = nums.size();
        dp.resize(n,-1);

        return solve(nums,0,k);
    }

    long long solve(vector<int>& nums, int idx, int k){
        if(idx > n-3) return 0;
        if(dp[idx] != -1) return dp[idx];
        long long op1 = max(0, k - nums[idx]) + solve(nums,idx + 1, k);
        long long op2 = max(0, k - nums[idx+1]) + solve(nums,idx + 2, k);
        long long op3 = max(0, k - nums[idx+2]) + solve(nums,idx + 3, k);

        dp[idx] = min(op1, min(op2,op3));

        return dp[idx];
    }
};

/*
此題想讓區間大於等於3中的subarray最大元素要大於等於k 
然後你可以對任意元素作+1 問說至少要做幾次操作
我們的目標是至少要顧到大小３的就好 其餘>3的肯定都顧得到
因此每次都從3個的範圍內挑出cost最低的選擇 在不斷往後看
*/
