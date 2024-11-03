/*
115. Distinct Subsequences
*/

//iterative TC: o(m*n) SC:o(m*n)
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size();
        int n = t.size();
        if(m == n) return s==t;
        if(m < n) return 0;
        s= "#"+s;
        t= "#"+t;

        vector<vector<long long>> dp(m+1, vector<long long>(n+1,0));
        dp[0][0] = 1;
        for(int i = 0; i<=m; i++){
            dp[i][0] = 1;
        }
        for(int j = 1; j<=n; j++){
            dp[0][j] = 0;
        }

        for(int i = 1; i<=m; i++){
            for(int j = 1; j<=n; j++){
                if(s[i] == t[j]){
                    dp[i][j] = min(LLONG_MAX/2,dp[i-1][j-1]+dp[i-1][j]);//s[i]派上用場的情況+ s[i]砍掉能否組成的情況
                    // min LLONG_MAX都是為了處理後項的溢出==
                }
                else dp[i][j] = dp[i-1][j];
            }
        }

        return dp[m][n];
    }
};

// 空間優化 TC: o(m*n) SC:o(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        if(n < m) return 0;
        if(n == m) return s == t;

        vector<int> dp(m+1); // s走i後有多少個subsequence 與t走到j相同
        dp[0]= 1;

        for(int i = 0; i < n; i++) {
            dp[0] = 1;
            for(int j = 0, leftUp = 1, backup; j < m; j++) {
                backup = dp[j+1];
                if(s[i] == t[j]) {
                    dp[j+1] = (leftUp + dp[j+1]) % MOD;
                }
                leftUp = backup;
            }
        }

        return dp[m];
    }
};

//recurison+memo TC: o(m*n) SC:o(m*n)
class Solution {
    int m,n;
    vector<vector<int>> memo;
public:
    int numDistinct(string s, string t) {
        m = s.size(); n = t.size();
        memo = vector<vector<int>>(m, vector<int>(n,-1));
        return dp(s,t,0,0);
    }

    int dp(string& s, string& t, int i, int j){
        if(j == n) return 1;
        if(m-i < n-j) return 0;

        if(memo[i][j] != -1) return memo[i][j];

        int res = 0;
        if(s[i] == t[j]){
            res = dp(s,t,i+1,j+1)+dp(s,t,i+1,j);
        }
        else res = dp(s,t,i+1,j);
        memo[i][j] = res;
        return res;
    }
};

/*
dp數組定義為在s[0...i]上與string t[0....j]上得最多子序列數目

解題思路：
求出現的子序列次數
也是two string converging類題 但是要注意dp數組如何更新數值
tc: o(m*n) sc:o(m*n)
*/
