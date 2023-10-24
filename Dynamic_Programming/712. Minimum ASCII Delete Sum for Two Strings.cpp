/*
712. Minimum ASCII Delete Sum for Two Strings
LCS相關題
*/


//iterative tc:O(m*n) sc:O(m*n)
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        int res = 0;
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        s1 = "#" + s1;
        s2 = "#" + s2;

        //base case
        dp[0][0] = 0;
        for(int i = 1; i<=m; i++){
            dp[i][0] = dp[i-1][0] + s1[i];
        }
        for(int j = 1; j<=n; j++){
            dp[0][j] = dp[0][j-1] + s2[j];
        }

        for(int i = 1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(s1[i] == s2[j]){
                    dp[i][j] =dp[i-1][j-1];//一樣代表不用刪會和前面一樣
                }
                else{
                    dp[i][j] = min(dp[i-1][j]+s1[i], dp[i][j-1]+s2[j]);//看刪哪個ascii小
                }
            }
        }
        return dp[m][n];
    }
};


/*
dp 兩個字串執行刪除 所需最少ASCII加起來為多少
dp[i][j] 從s1[1:i] s2[1:j]需要刪除的最小ASCII sum
*/


//recursion +memo -> 記體體容量不足
class Solution {
    //recursion++memo
    vector<vector<int>> memo;
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.size();
        int n = s2.size();
        memo = vector<vector<int>>(m+1, vector<int>(n+1, -1));
        //base case:
        s1 = "#"+s1;
        s2 = "#"+s2;
        memo[0][0] = 0;
        for(int i = 1; i<=m; i++){
            memo[i][0] = memo[i-1][0] + s1[i];
        }

        for(int j = 1; j<=n; j++){
            memo[0][j] = memo[0][j-1] + s2[j];
        }
        //dp定義從s1[1:i] s2[1:j]刪除後最少的ASCII 是多少
        return dp(s1,s2,m,n);
    }

    int dp(string s1, string s2, int i, int j){
        if(i == 0 || j == 0) return memo[i][j];
        if(memo[i][j] !=-1) return memo[i][j];

        if(s1[i] == s2[j]){
            return memo[i][j] = dp(s1,s2,i-1,j-1);
        }
        else return memo[i][j] = min(dp(s1,s2,i-1,j)+s1[i], dp(s1,s2,i,j-1)+s2[j]);
    }
};

/*
这段代码的内存超限问题可能出现在递归深度过深的情况下，导致了memo数组中需要存储大量的中间结果，占用了大量的内存空间。
由于递归调用的深度受到输入字符串长度的限制，如果输入字符串非常长，递归深度将会变得非常大，进而导致内存超限的问题。
要解决这个问题，可以尝试使用动态规划的迭代方法，而不是递归。迭代方法通常使用一个二维数组来存储中间结果，避免了递归调用的深度。
*/


