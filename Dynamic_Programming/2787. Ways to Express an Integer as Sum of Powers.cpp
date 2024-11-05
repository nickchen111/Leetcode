/*
2787. Ways to Express an Integer as Sum of Powers
*/

//遞推 + 遞歸 
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numberOfWays(int n, int x) {
        auto quickMul = [&](LL a, LL b) -> LL {
            LL ans = 1;
            while(b) {
                if(b & 1) ans = (ans * a) % MOD;
                a = (a*a) % MOD;
                b >>= 1;
            }

            return ans;
        };

        // TC:O(n * lgx)
        vector<LL> pow(n+1);
        for(int i = 1; i <= n; i++) {
            pow[i] = quickMul(i,x);
        }

        // TC:O(n^2*lgx) SC:O(n) -> TC:O(n^2) SC:O(n)

        vector<LL> dp(n+1);
        dp[0] = 1;
        for(int i = 1; i <= n; i++) {
            // int pow = quickMul(i,x);
            for(int j = n; j >= pow[i]; j--) {
                dp[j] = (dp[j] + dp[j - pow[i]]) % MOD;
            }
        }

        return dp[n];
        /*
        遞推 TC:O(n^2 * lgx) SC:O(n^2)
        vector<vector<LL>> dp(n+1, vector<LL>(n+1,0)); // 用到第i個數字時 可以拼湊出 j的數量有多少
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = n; j >= 0; j--) {
                dp[i][j] = dp[i-1][j];
                if(j - quickMul(i,x) >= 0) {
                    dp[i][j] = (dp[i][j] + dp[i-1][j - quickMul(i,x)]) % MOD;
                }
            }
        }

        return dp[n][n];
        */
        /*
        遞歸 TC:O(n^2 * lgx) SC:O(n^2)
        vector<vector<LL>> memo(n+1, vector<LL>(n, -1));
        function<LL(int i, int sum)> dfs = [&](int i, int sum) -> LL {
            if(sum == n) return 1;
            if(sum > n) return 0;
            if(i > n) return 0;
            if(memo[i][sum] != -1) return memo[i][sum];
            return memo[i][sum] = (dfs(i+1, sum) + dfs(i+1, sum + quickMul(i,x))) % MOD;
        };

        return dfs(1, 0);

        */
    }
};


//  TC:O(target*n) SC:O(target)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfWays(int n, int x) {
        vector<LL> dp(n+1);
        dp[0] = 1;
        // x次方 
        for(int i = 1; pow(i,x) <= n; i++){
            for(int sum = n; sum >= pow(i,x); sum--){
                dp[sum] += dp[sum-pow(i,x)];
            }
        }

        return dp[n]%M;

    }
};

// 第二種多開數組寫法 TC:O(target*n) SC:O(target)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfWays(int n, int x) {
        vector<LL> dp(n+1);
        dp[0] = 1;
        // x次方 
        for(int i = 1; pow(i,x) <= n; i++){
            auto dp_tmp = dp;
            for(int sum = 0; sum <= n ; sum++){
                if(pow(i,x) > sum) continue;
                dp[sum] += dp_tmp[sum-pow(i,x)];
            }
        }

        return dp[n]%M;

    }
};


/*
很像之前的279 DP題 某個數字拆解後的平方最大值
但這題其實不太一樣 這題要問說 某個數 能否用某些數的x次方拼湊出的可能性有多少
所以 3^2+1^2 跟 1^2+3^2這種的要算是同一種不能重複計算 並且每個數字只能用一次 明顯的01背包問題
*/
