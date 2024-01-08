/*
1911. Maximum Alternating Subsequence Sum
*/

// DP TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(),0);
        vector<LL> dp(n+1,INT_MIN/2);
        dp[0] = 0;
        LL rollMin = 0;
        LL res = 0;
        for(int i = 1; i <= n; i++){
            dp[i] = max((LL)nums[i], max(dp[i-1], (LL)nums[i]-rollMin));
            rollMin = min(rollMin, nums[i]-dp[i-1]);
            res = max(res, dp[i]);
        }

        return res;
    }
};

//Greedy TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        LL res = 0;
        for(int i = 0; i < n; i++){
            if(i+1 < n && nums[i] > nums[i+1]){
                res += (nums[i] - nums[i+1]);
            }
        }

        res += nums.back();
        return res;
    }
};

/*
此題想求偶數位間隔元素相加 扣掉奇數位的最大值 可以讓給定的數組隨機選取元素在排列出array
首先偶數減奇數 會想說肯定是要讓偶數盡量大 奇數盡量小
這題很像變形版house robber 一樣是選or不選 隔壁不能選
選了一個然後去看之前的一定會想選進量小的去減去 做rollingMin
貪心的作法跟122股票買賣一樣
遇到降序排列就一直對現在數字取正 後面數字取負 最後一個數字沒有比較對象直接加入答案
*/
