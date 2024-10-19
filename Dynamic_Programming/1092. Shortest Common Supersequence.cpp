/*
1092. Shortest Common Supersequence
*/


// Recursion TC:O(m*n) SC:O(m*n)
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        // Recursion
        int m = str1.size();
        int n = str2.size();
        vector<vector<int>> memo(m, vector<int>(n, -1));

        function<int(int, int)> DFS = [&](int i, int j) -> int {
            if(i < 0) return j + 1;
            if(j < 0) return i + 1;

            if(memo[i][j] != -1) return memo[i][j];

            if(str1[i] == str2[j]) {
                return memo[i][j] = DFS(i-1, j-1) + 1;
            }
            
            return memo[i][j] = min(DFS(i-1, j), DFS(i, j-1)) + 1;
        };

        function<string(int, int)> make_ans = [&](int i, int j) -> string{
            if(i < 0) return str2.substr(0, j+1);
            if(j < 0) return str1.substr(0, i+1);

            if(str1[i] == str2[j]) {
                return make_ans(i-1, j-1) + str1[i];
            }

            if(DFS(i,j) == DFS(i-1,j) + 1) return make_ans(i-1, j) + str1[i];
            
            return make_ans(i, j-1) + str2[j];
        };

        return make_ans(m-1,n-1);
    }
};



// SCS Iterative TC:O(m*n) SC:O(m*n)
class Solution {
    //SCS
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(); int n = str2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));

        //base case
        for(int i = 0; i<=m; i++){
            dp[i][0] = i;
        }

        for(int j = 0; j<=n; j++){
            dp[0][j] = j;
        }

        for(int i = 1; i<=m;i++){
            for(int j =1; j<=n; j++){
                if(str1[i-1] == str2[j-1]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{
                    dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);
                }
            }
        }
        
        //重構SDS
        string ans;
        int i = m; int j = n;
        while(i > 0 && j > 0){
            if(str1[i-1] == str2[j-1]){
                ans += str1[i-1];
                i--;j--;
            }
            else if(dp[i][j] == dp[i-1][j]+1){
                ans += str1[i-1];
                i--;
            }
            else{
                ans +=str2[j-1];
                j--;
            }
        }
        while(i > 0){
            ans += str1[i-1];
            i--;
        }
        while(j>0){
            ans+=str2[j-1];
            j--;
        }
        reverse(ans.begin(), ans.end());

        return ans;
    }
};

//用LCS概念建構DP數組
class Solution {
    //LCS
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size(); int n = str2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        //狀態轉移

        for(int i = 1; i<=m;i++){
            for(int j =1; j<=n; j++){
                if(str1[i-1] == str2[j-1]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        //重構SDS
        string ans;
        int i = m; int j = n;
        while(i > 0 && j > 0){
            if(str1[i-1] == str2[j-1]){
                ans += str1[i-1];
                i--;j--;
            }
            else if(dp[i][j] == dp[i-1][j]){
                ans += str1[i-1];
                i--;
            }
            else{
                ans +=str2[j-1];
                j--;
            }
        }
        while(i > 0){
            ans += str1[i-1];
            i--;
        }
        while(j>0){
            ans+=str2[j-1];
            j--;
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};

/*
解題思路：
1.直接用SCS做 shortest common supersequence
dp[i][j]定義 str1[0:i] str2[0:j]的SCS
xxxxxxx a
yyyyy b
2.用LCS概念去做
dp[i][j] 定義 str[0:i] str2[0:j]的最長公共子串
xxxxxx a
yyyy b

tc: O(m*n) sc:O(m*n)
*/
