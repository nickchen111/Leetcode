/*
70. Climbing Stairs
*/

// 矩陣快速冪 TC:O(lgn) SC:O(2*4)
class Solution {
    using LL = long long;
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        vector<vector<LL>> arr = {{1, 1}}; // 第一項，第零項
        vector<vector<LL>> m = {{1, 1}, {1, 0}};

        return multiply(arr, pow(m, n-1))[0][0];
    }
    vector<vector<LL>> multiply(const vector<vector<LL>>& a, const vector<vector<LL>>& b) {
        int n = a.size();
        int m = b[0].size();
        int k = a[0].size();
        vector<vector<LL>> res(n, vector<LL>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int c = 0; c < k; c++) { 
                    res[i][j] = (res[i][j] + (LL)a[i][c] * b[c][j]);
                }
            }
        }
        return res;
    }

    vector<vector<LL>> pow(vector<vector<LL>>& m, int p) {
        int n = m.size();
        vector<vector<LL>> res(n, vector<LL>(n));
        for (int i = 0; i < n; i++) {
            res[i][i] = 1; // 單位矩陣
        }

        for(; p != 0; p >>= 1) {
            if(p & 1) {
                res = multiply(res, m);
            }
            m = multiply(m, m);
        }
        return res;
    }
};

//iterative tc: O(n) sc: O(n) 可在優化
class Solution {
    //iterative 
public:
    int climbStairs(int n) {
        if(n == 1 || n == 2) return n;
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;

        for(int i = 3; i<=n; i++){
            dp[i] = dp[i-1]+dp[i-2];
        }

        return dp[n];
    }
};


//優化 tc:O(n) sc: O(1)
class Solution {
    //iterative 
public:
    int climbStairs(int n) {
        if(n == 1 || n == 2) return n;

        int prev = 1;
        int cur = 2;

        for(int i = 3; i<=n; i++){
            int sum = prev+cur;
            prev = cur;
            cur = sum;
        }

        return cur;
    }
};

//recursion+memo 
class Solution {
    //recursion+memo
    vector<int> memo;
public:
    int climbStairs(int n) {
        memo = vector<int>(n+1, -1);

        return backtrack(n);
    }
    int backtrack(int n){
        if(n == 1 || n == 2) return n;
        if(memo[n] != -1) return memo[n];

        int res = backtrack(n-1) + backtrack(n-2); 
        memo[n] = res;

        return res;
    }
};
