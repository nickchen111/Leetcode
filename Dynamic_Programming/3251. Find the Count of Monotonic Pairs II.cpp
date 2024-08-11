/*
3251. Find the Count of Monotonic Pairs II
*/

// TC:O(n*m) SC:O(m*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size();
        int maxnum = *max_element(nums.begin(), nums.end());
        vector<vector<LL>> dp(n+1, vector<LL>(maxnum+1));
        nums.insert(nums.begin(), -1);
        for(int i = 0; i <= nums[1]; i++){
            dp[1][i] = 1;
        }
        
        for(int i = 2; i <= n; i++){
            int maxVal = max(nums[i], nums[i-1]);
            vector<LL> presum(maxVal+1);
            for(int k = 0; k <= maxVal; k++){
                presum[k] = (k-1 < 0 ? 0 : presum[k-1]) + dp[i-1][k];
            }
            for(int j = 0; j <= nums[i]; j++){
                int minVal = min(j, nums[i-1]-nums[i]+j);
                dp[i][j] = (minVal >= 0 ? presum[minVal] : 0);
                dp[i][j] %= M;
            }
        }
        
        int res = 0;
        for(int i = 0; i <= nums[n]; i++){
            res = (res + dp[n][i]) % M;
        }
    
        
        return res;
    }
};


/*
k代表之前的數字, j代表這次要求的數字
k <= j
nums[i-1]-k >= nums[i]-j -> k <= nums[i-1] - nums[i] + j; k代表之前的數字
k = min(j, nums[i-1] - nums[i] + j) 
為何不能直接用j-1 來求前綴和 因為j-1的數值可能不滿足題目要求的規律 這就是為什麼這題要用數學公式來求出
*/
