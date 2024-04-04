/*
3082. Find the Sum of the Power of All Subsequences
*/


// 4/4 
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    LL dp[105][105][105];
public:
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();
        nums.insert(nums.begin(), -1);
        dp[0][0][0] = 1;
        for(int i = 1; i <= n; i++){
            for(int s = 0; s <= k; s++){
                for(int j = 0; j <= i; j++){
                    dp[i][s][j] = dp[i-1][s][j];
                    if(s - nums[i] >= 0 && j >= 1) dp[i][s][j] += dp[i-1][s-nums[i]][j-1];
                    dp[i][s][j] %= M;
                }
            }
        }
        
        LL res = 0;
        for(int j = 1; j <= n; j++){
            LL t = dp[n][k][j];
            res = (res + quickMul(2, n - j)*t) % M;
        }

        return res;
    }
    LL quickMul(LL a, LL b){
        if(b == 0) return 1;
        LL y = quickMul(a, b/2);
        if(b % 2){
            return (y%M*y%M)*a%M;
        }
        else return (y%M*y%M);
    }
};

// bottom up 
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<vector<LL>>> dp(n+1, vector<vector<LL>>(k+1, vector<LL>(n+1,-1)));
    
        return DFS(0, n, k, nums, dp) % M;
    }
    LL DFS(int index, int n, int remain, vector<int>& nums, vector<vector<vector<LL>>>& dp){
        if(dp[index][remain][n] == -1){
            if(remain == 0){
                dp[index][remain][n] = quickMul(2,n);
            }
            else {
                dp[index][remain][n] = 0;
                for(int i = index; i < nums.size(); i++){
                    if(nums[i] <= remain) dp[index][remain][n] = (dp[index][remain][n] + DFS(i+1,n-1, remain-nums[i], nums, dp))%M;
                }
                
            }
        }
        return dp[index][remain][n];
    }
    
    LL quickMul(LL x, LL n) {
        if (n == 0) {
            return 1;
        }
        LL y = quickMul(x, n / 2) % M;
        if(n%2){
          return (y*y%M)*x%M;
        }
        else return y*y%M;
    }


// top down TLE  exceed
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int sumOfPower(vector<int>& nums, int k) {
        LL res = 0;
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        
        vector<vector<int>> dp(k+1); //走到某個位置可以變成某sum所需數字量為多少 sum-> pos
        
        dp[0].push_back(0); // 0個數字能夠得到sum = 0 需要的數字量
        for(int i = 1; i <= n; i++){
            for(int sum = k; sum-nums[i] >= 0; sum--){
                for(int k = 0; k < dp[sum-nums[i]].size(); k++){
                    dp[sum].push_back(dp[sum-nums[i]][k]+1);
                }
            }
        }
        
       
        for(int j = 0; j < dp[k].size(); j++){
            res = (res + quickMul(2, n-dp[k][j])) % M;
        }

    
        return res;
    }
    
    LL quickMul(LL x, LL n) {
        if (n == 0) {
            return 1;
        }
        LL y = quickMul(x, n / 2) % M;
        if(n%2){
          return (y*y%M)*x%M;
        }
        else return y*y%M;
    }
};

/*
問說有多少個subsequence sum = k
他是問每一種subsequence裡面有多少種組合sum = k
可以組成k的元素們必選 有哪些選法

n只有到100 !? 
n^3可以接受
單純問說subsequence可選可不選 ＋＋到sum就是背包問題
現在多了一個試問各種subsequece的可能性

*/
