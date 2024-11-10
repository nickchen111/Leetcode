/*
3351. Sum of Good Subsequences
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        
        unordered_map<LL,LL> map; // 某數字的出現數量
        unordered_map<LL, LL> sum; // 以某個數字結尾的加總?
        int n = nums.size();
       
        LL res = 0;
        for(int i = 0; i < n; i++) {
            sum[nums[i]] = (sum[nums[i]] + map[nums[i]-1] * nums[i] + sum[nums[i]-1]) % MOD;
            sum[nums[i]] = (sum[nums[i]] + map[nums[i]+1] * nums[i] + sum[nums[i]+1]) % MOD;
            sum[nums[i]] = (sum[nums[i]] + nums[i]) % MOD;
            map[nums[i]] = (map[nums[i]-1] + map[nums[i]+1] + 1 + map[nums[i]]) % MOD;
        }     
        
        for(auto &[key, val] : sum) {
            res = (res + val) % MOD;
        }
        return res;
        
    }
};


/*
1 2 1排序
1 1 2 會少算 1 2 1
*/
