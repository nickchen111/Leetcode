/*
10. Regular Expression Matching
*/

// 2025.02.12
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = true;
        for(int j = 1; j < n; j++) {
            if(p[j] == '*') dp[0][j+1] = dp[0][j-1];
        }
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(s[i] == p[j] || p[j] == '.') {
                    dp[i+1][j+1] = dp[i][j];
                }
                else if(p[j] == '*') {
                    bool tmp1 = dp[i+1][j-1];
                    bool tmp2 = j-1 >= 0 ? ((p[j-1] == s[i] || p[j-1] == '.') && dp[i][j+1]) : false;
                    dp[i+1][j+1] = tmp1 || tmp2;
                }
            }
        }
        return dp[m][n];
        /*
        遞歸
        vector memo(m+1, vector<int>(n+1, -1));

        auto dfs = [&](auto &&dfs, int i, int j) -> bool {
            if(j == n) return i == m;
            if(memo[i][j] != -1) return memo[i][j];
            bool ret = false;
            bool first_match = (i < m && (s[i] == p[j] || p[j] == '.'));
            if(j+1 < n && p[j+1] == '*') { 
                // * 匹配 0 次 or 多次
                ret = dfs(dfs, i, j+2) || (first_match && dfs(dfs, i+1, j));
            } else {
                ret = first_match && dfs(dfs, i+1, j+1);
            }

            return memo[i][j] = ret;
        };

        return dfs(dfs, 0, 0);
        */
    }
};


// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(); int n = p.size();
        s = "#"+s;
        p = "#"+p;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        //base case
        dp[0][0] = 1;
        //當s or p其中之為空 dp = 0;

        //當 p有東西 但他也有可能會是 Y*Y*Y* 這種情況下他可以變成空
        for(int j = 2; j<=n; j++){
            if(p[j] == '*') dp[0][j] = dp[0][j-2];
        }
 
        for(int i = 1; i<=m; i++){
            for(int j = 1;j<=n;j++){
                if(isalpha(p[j])){
                    dp[i][j] = (s[i] == p[j] && dp[i-1][j-1]);
                }
                else if(p[j] == '.') dp[i][j] = dp[i-1][j-1];

                else if(p[j] == '*'){
                    bool temp1 = dp[i][j-2];
                    bool temp2 = dp[i-1][j] && (s[i] == p[j-1] || p[j-1] == '.');
                    dp[i][j] = temp1 || temp2;
                }
            }
        }
        return dp[m][n];
    }
};

/*
此題要想到是two string convering的dp題
一樣是去考慮s[i] p[j]相等不相等情況
不過這題的p的字符有可能是 . * 需要再分情況討論
考點
1.字符的特殊情況
2.邊界條件思考
dp[i][j]: s[1:i] p[1:j]是否可以符合regular expression
*/
