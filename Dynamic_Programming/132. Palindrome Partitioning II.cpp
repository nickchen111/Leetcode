/*
132. Palindrome Partitioning II
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        s = "#" + s;
        vector<vector<bool>> dp_check(n+1, vector<bool>(n+1));
        for(int i = 1; i <= n; i++){
            dp_check[i][i] = 1;
        }
        for(int i = 2; i <= n; i++){
            if(s[i] == s[i-1]){
                dp_check[i-1][i] = 1;
            }
        }

        for(int len = 3; len <= n+1; len++){
            for(int i = 1; i + len -1 <= n; i++){
                int j = i + len - 1;
                if(s[i] == s[j] && dp_check[i+1][j-1]) dp_check[i][j] = 1;
            }
        }

        vector<int> dp(n+1, INT_MAX/2);
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = i; j <= n; j++){
                if(dp_check[i][j]) dp[j] = min(dp[j],dp[i-1]+1);
            }
        }

        return dp[n]-1;
    }
};

/*
這題想求出一個字串最少可以切割成幾份讓所有substring皆是回文串
一樣可以用dp求解 先用區間dp方法求出每個區間是否是回文串 減少每次都要判斷的時間
在用n^2的方式去切割出所有的可能性 dp[i]定義成切割到i這裡為止最少需要切割出多少的字串能使他為回文串
*/
