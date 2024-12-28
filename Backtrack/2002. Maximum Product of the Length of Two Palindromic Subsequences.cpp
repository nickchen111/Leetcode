/*
2002. Maximum Product of the Length of Two Palindromic Subsequences
*/

// 2024.12.28 狀壓 + 區間DP TC:O(2^n*n^2) SC:O(n^2 + 2^n) n = 12
class Solution {
public:
    int maxProduct(string s) {
        int n = s.size();
        int mask = (1 << n) - 1;
        int ret = 0;
        auto lcp = [&](int submask) -> int {
            string t;
            for(int j = 0; j < n; j++) {
                if((submask >> j) & 1) {
                    t += s[j];
                }
            }
            int m = t.size();
            if(m == 0) return 0;
            vector<vector<int>> dp(m, vector<int>(m));
            for(int i = 0; i < m; i++) dp[i][i] = 1;
            for(int i = 0; i < m; i++) {
                for(int j = i-1; j >= 0; j--) {
                    if(t[i] == t[j]) {
                        dp[j][i] = dp[j+1][i-1] + 2;
                    }
                    else dp[j][i] = max(dp[j+1][i], dp[j][i-1]);
                }
            }

            return dp[0][m-1];
        };
        int submask = mask;
        vector<int> memo((1<<n), -1);
        while(submask) {
            int remaining_mask = submask ^ mask;
            int cand1 = 0, cand2 = 0;
            if(memo[remaining_mask] != -1) cand1 = memo[remaining_mask];
            else memo[remaining_mask] = cand1 = lcp(remaining_mask);
            if(memo[submask] != -1) cand2 = memo[submask];
            else memo[submask] = cand2 = lcp(submask);
            ret = max(ret, cand1 * cand2);
            submask = (submask-1) & mask;
        }

        return ret;
    }
};

// Concise TC:O(2^n*n^2) SC:O(n^2) n = 12
class Solution {
    
public:
    int maxProduct(string s) {
        int n = s.size();
        int res = 0;
        for(int subset = 1; subset < (1<<n)-1; subset++){
            res = max(res, lps(s,subset) * lps(s, (1<<n)-1-subset));
        }

        return res;
    }

    int lps(string& s, int state){
        string str1;
       
        for(int i = 0; i < s.size(); i++){
            int temp = (state>>i)&1;
            if(temp) str1.push_back(s[i]);
        }

        int n = str1.size();
        
        vector<vector<int>> dp(n,vector<int>(n));

        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
        }

    
        for(int len = 2; len <= n; len++){
            for(int i = 0; i + len -1 < n; i++){
                int j = i + len - 1;
                if(str1[i] == str1[j]){
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
                else dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
            }
        }

        return dp[0][n-1];
    }
};


// Backtrack TC:O(2^n*n^2) SC:O(n^2) n = 12
class Solution {
    int res = -1;
public:
    int maxProduct(string s) {
        
        backtrack(s,0, 0);

        return res;
    }

    void backtrack(string& s, int idx, int cur){
        if(idx == s.size()){
            res = max(res, check(s,cur));
            return;
        }
      
        backtrack(s, idx+1, cur + (1 << idx));
        backtrack(s, idx+1, cur);
    }
    int check(string& s, int cur){
        string str1;
        string str2;
       
        for(int i = 0; i < s.size(); i++){
            int temp = (cur>>i)&1;
            if(temp) str1.push_back(s[i]);
            else str2.push_back(s[i]);
        }

        return helper(str1) * helper(str2);
    }

    int helper(string& str1){
        
        int m = str1.size();
        if(m == 0) return 0;
        vector<vector<int>> dp1(m,vector<int>(m));

        for(int i = 0; i < m; i++){
            dp1[i][i] = 1;
        }

        for(int i = 1; i < m; i++){
            if(str1[i] == str1[i-1]){
                dp1[i-1][i] = 2;
            }
            else dp1[i-1][i] = 1;
        }
    
        for(int len = 3; len <= m; len++){
            for(int i = 0; i + len -1 < m; i++){
                int j = i + len - 1;
                if(str1[i] == str1[j]){
                    dp1[i][j] = dp1[i+1][j-1] + 2;
                }
                else dp1[i][j] = max(dp1[i+1][j], dp1[i][j-1]);
            }
        }


        return dp1[0][m-1];
    }
};


/*
一串字串選兩個subsequence 兩個不能重複選相同index
問說怎麼選能讓這兩個字串選出來的長度乘積最大
兩個字串要都是回文串
x         x
   y.         y
我的想法是用回溯讓他任意選 然後選到沒東西後去讓剩下的配出回文看能多長 跟目前配出的看能多長
*/
