/*
392. Is Subsequence
*/



// Two pointer TC:O(n) SC:O(1)
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int m = s.size();
        int n = t.size();
        int p1 = 0;
        int p2 = 0;
        while(p2 < n){
            if(s[p1] == t[p2]){
                p1++;
                p2++;
            }
            else {
                p2++;
            }
        }

        return p1 == m ? true:false;
    }
};

// DP TC:O(m*n) SC:O(m*n)
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int m = s.size();
        int n = t.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1,0));
        s = "#" + s;
        t = "#" + t;
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=m; j++){
                if(j > i) continue;
                if(s[j] == t[i]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }

        return dp[n][m] == m ? true:false;
    }
};
