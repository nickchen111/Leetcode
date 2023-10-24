/*
131. Palindrome Partitioning
*/


class Solution {
    //改用dp來判斷回文串
    int dp[16][16]; //從s[i:j]是否為回文串
    vector<vector<string>>  res;
    vector<string> track;
public:
    vector<vector<string>> partition(string s) {
        //backtrack
        int n = s.size();
        //一個字的時候
        for(int i = 0; i<n; i++){
            dp[i][i] = 1;
        }
        for(int i = 0; i+1< n; i++){
            dp[i][i+1] = s[i] == s[i+1] ? true:false;
        }

        //這樣就不用在backtrack裡面每次都去判斷是否回文 如果每次都判斷就會在backtrack時間複雜度基礎上乘上n
        //如果用dp 就是O(n^2 + backtrack時間複雜度)
        for(int len = 3; len<=n;len++){//n方做預處理
            for(int i = 0; i+len-1<n; i++){
                int j = i+len-1;
                if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = true;
                }
                else dp[i][j] = false;
            }
        }

        backtrack(s, 0);
        return res;
    }
    void backtrack(string& s, int cur){
        int n = s.size();
        if(cur == n){
            res.push_back(track);
            return;
        }
        for(int i =cur; i < n; i++){
            if(dp[cur][i]){
                track.push_back(s.substr(cur, i-cur+1));
                backtrack(s, i+1);
                track.pop_back();
            }
        }
    }
};
