/*
3320. Count The Number of Winning Sequences
*/


// TC:O(9 * (n*(n-1)/2)) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countWinningSequences(string s) {
        int n = s.size();
        int offset = n;
        vector<vector<LL>> dp(2*n+1, vector<LL>(3, 0)); // 0 : F, 1 : W, 2 : E
        if(s[0] == 'F') {
            dp[0+offset][0] = 1;
            dp[1+offset][1] = 1;
            dp[-1+offset][2] = 1;
        }
        else if(s[0] == 'E') {
            dp[1+offset][0] = 1;
            dp[-1+offset][1] = 1;
            dp[0+offset][2] = 1;
        } 
        else {
            dp[-1+offset][0] = 1;
            dp[0+offset][1] = 1;
            dp[1+offset][2] = 1;
        }
        
        for(int i = 1; i < n;  i++){
            vector<vector<LL>> dp_cur(2*n+1, vector<LL>(3, 0));
            for(int j = i+offset+1; j >= offset-i-1; j--) {
                for(int k = 0; k < 3; k++){
                    if(dp[j][k] > 0) {
                        if(s[i] == 'F') {
                            for(int t = 0; t < 3; t++) {
                                if(t == k) continue;
                                if(t == 2) {
                                    dp_cur[j-1][t] = (dp_cur[j-1][t] + dp[j][k]) % M;
                                }
                                else if(t == 1){
                                    dp_cur[j+1][t] = (dp_cur[j+1][t] + dp[j][k]) % M;
                                }
                                else dp_cur[j][t] = (dp_cur[j][t] + dp[j][k]) % M;
                            }
                        }
                        else if(s[i] == 'W') {
                            for(int t = 0; t < 3; t++) {
                                if(t == k) continue;
                                if(t == 2) {
                                    dp_cur[j+1][t] = (dp_cur[j+1][t] + dp[j][k]) % M;
                                }
                                else if(t == 1){
                                    dp_cur[j][t] = (dp_cur[j][t] + dp[j][k]) % M;
                                }
                                else dp_cur[j-1][t] = (dp_cur[j-1][t] + dp[j][k]) % M;
                            }
                        }
                        else {
                            for(int t = 0; t < 3; t++) {
                                if(t == k) continue;
                                if(t == 2) {
                                    dp_cur[j][t] = (dp_cur[j][t] + dp[j][k]) % M;
                                }
                                else if(t == 1){
                                    dp_cur[j-1][t] = (dp_cur[j-1][t] + dp[j][k]) % M;
                                }
                                else dp_cur[j+1][t] = (dp_cur[j+1][t] + dp[j][k]) % M;
                            }
                        }
                    }
                }
            }
            dp = dp_cur;
        }
        
        LL res = 0;
        for(int i = offset+1; i <= 2*n; i++) {
            for(int j = 0; j < 3; j++) {
                res = (res + dp[i][j]) % M;
            }
        }
        
        return res;
        
    }
};

/*
已知 alice召喚的順序，bob不能連續召喚相同神獸
問說bob能贏的distinct sequence 
F > E
W > F
E > W
vector<vector<vector<LL>>> dp 走到i為止 bob出? 可以獲得的分數的每種排列組合可能性?
*/
