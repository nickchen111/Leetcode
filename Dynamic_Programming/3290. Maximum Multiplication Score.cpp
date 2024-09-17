/*
3290. Maximum Multiplication Score
*/


// Iterative 優化TC:O(n*5) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<LL> dp(5, LLONG_MIN/2);
        dp[0] = 0;
        b.insert(b.begin(), -1);
        a.insert(a.begin(), -1);
        for(int i = 1; i <= n; i++){
            auto dp_tmp = dp;
            for(int j = 1; j <= 4; j++){
                if(i < j) break;
                dp[j] = max(dp_tmp[j], dp_tmp[j-1] + (LL)a[j]*b[i]);
            }
        }

        return dp[4];
    }
};


// Iterative 未優化TC:O(n*5) SC:O(n*5)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<LL>> dp(n+1, vector<LL>(5, LLONG_MIN/3));
        b.insert(b.begin(), -1);
        a.insert(a.begin(), -1);
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j <= 4; j++){
                if(i < j) break;
                dp[i][j] = dp[i-1][j];
                if(j)
                    dp[i][j] = max(dp[i][j], dp[i-1][j-1] + (LL)a[j]*b[i]);
            }
        }

        return dp[n][4];
    }
};



// Recursion + Memo TC:O(4*n) SC:O(n*4)
class Solution {
    using LL = long long;
    LL res = LLONG_MIN;
    vector<vector<LL>> memo;
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = a.size();
        int m = b.size();

        memo.resize(m, vector<LL>(n, LLONG_MIN/2));
    
        return DFS(a,b, m-1, n-1);
    }
    LL DFS(vector<int>& a, vector<int>& b, int i, int j){
        if(j < 0) return 0;
        if(i < 0) return LLONG_MIN/2;
        if(memo[i][j] != LLONG_MIN/2) return memo[i][j];

        LL res = max(DFS(a,b, i-1,j), DFS(a,b, i-1,j-1) + (LL)a[j]*b[i]);

        memo[i][j] = res;
        return res;

    }
};


