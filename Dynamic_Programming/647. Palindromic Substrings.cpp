/*
647. Palindromic Substrings
*/


//判斷回文串的方式 TC:O(n^2) SC:O(1)
class Solution {
    int res = 0;
public:
    int countSubstrings(string s) {
      
        for(int i = 0; i<s.size(); i++){
            countPalindrome(s,i,i+1);
            countPalindrome(s,i,i);
        }
        return res;
    }
    void countPalindrome(string& s, int left, int right){
        while(left >=0 && right<s.size() && s[left] == s[right]){
            left--;
            right++;
            res++;
        }
    }
};

//區間型DP TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int countSubstrings(string s) {
        //區間DP
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,0));
        int res = n;
        for(int i = 0; i<n; i++){
            dp[i][i] = 1;
        }

        for(int i = 0; i<n-1; i++){
            if(s[i] == s[i+1]){
                dp[i][i+1] = 2;
                res+=1;
            }
        }

        for(int len = 3; len<=n; len++){
            for(int i = 0; i+len-1<n; i++){
                int j = i+len-1;
                if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = dp[i+1][j-1]+1;
                    res+=1;
                }
            }
        }
        
        return res;
    }
};
