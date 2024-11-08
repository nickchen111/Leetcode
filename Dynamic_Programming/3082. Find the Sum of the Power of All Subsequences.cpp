/*
3082. Find the Sum of the Power of All Subsequences
*/

// 遞推 + 遞歸
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int sumOfPower(vector<int>& nums, int k) {
        int n = nums.size();
        vector<LL> power(n+1);
        power[0] = 1;
        for(int i = 1; i <= n; i++) {
            power[i] = (power[i-1] * 2 ) % MOD;
        }

        // TC:O(n*n*k) SC:O(n*k)
        vector<vector<LL>> dp(n+1, vector<LL>(k+1,0));
        dp[0][0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j >= 1; j--) {
                for(int t = k; t >= nums[i]; t--) {
                    if(dp[j-1][t-nums[i]]) {
                        dp[j][t] = (dp[j][t] + dp[j-1][t-nums[i]]) % MOD;
                    }
                }
            }
        }
        /*
        遞推 TC:O(n*n*k) SC:O(n*n*k)
        vector<vector<vector<LL>>> dp(n+1, vector<vector<LL>>(n+1, vector<LL>(k+1, 0)));
        dp[0][0][0] = 1; // 0-1的index 在 0個選擇 可以加總出0的子序列方案數量
        // 每個i只會和前一個i-1中的 cnt or cnt-1有關係 sum 的話就是從大到小
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j >= 0; j--) {
                for(int t = k; t >= 0; t--) {
                    dp[i+1][j][t] = dp[i][j][t];
                    if(t - nums[i] >= 0 && j-1 >= 0 && dp[i][j-1][t-nums[i]]) {
                        dp[i+1][j][t] = (dp[i+1][j][t] + dp[i][j-1][t-nums[i]]) % MOD;
                    }
                }
            }
        }
        */

        LL res = 0;
        for(int j = 0; j <= n; j++) {
            // res = (res + dp[n][j][k] * power[n-j]) % MOD;
            res = (res + dp[j][k] * power[n-j]) % MOD;
        }

        return res;
        // 如果發現有x個數字可以形成 target 那麼 他們以外的 都跟他們當成是子序列的數量就是 (1 << n - x)
        /*
        遞歸 TC:O(n*n*k) SC:O(n*n*k)
        vector<vector<vector<LL>>> memo(n, vector<vector<LL>>(n+1, vector<LL>(k+1,-1)));
        function<LL(int i, LL sum, LL cnt)> dfs = [&](int i, LL sum, LL cnt) -> int {
            if(sum > k) return 0;
            if(i < 0) {
                if(sum == k) {
                    return power[n-cnt];
                }
                else return 0;
            }
            if(memo[i][cnt][sum] != -1) return memo[i][cnt][sum];

            return memo[i][cnt][sum] = (dfs(i-1, sum, cnt) + dfs(i-1, sum + nums[i], cnt+1)) % MOD;
        };

        return dfs(n-1, 0, 0);
        */
    }
};


// 4/4  TC:O(n^3) SC:O(n^3)
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
