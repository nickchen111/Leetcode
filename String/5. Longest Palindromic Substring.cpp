/*
5. Longest Palindromic Substring
*/

// Manacher TC:O(n) SC:O(n)
class Solution {
public:
    string longestPalindrome(string s) {
        // Manacher
        int n = s.size();
        string t = "#";
        for(auto &ch : s) {
            t += ch;
            t += "#";
        }

        vector<int> p(2*n+1);
        for(int i = 0, c = 0, r = 0, len; i < 2*n+1; i++) {
            len = r > i ? min(p[2*c-i], r-i) : 1;
            while(i + len < 2*n+1 && i - len >= 0 && t[i+len] == t[i-len]) {
                len ++;
            }
            if(i + len > r) {
                r = i + len;
                c = i;
            }
            p[i] = len;
        }

        int len = 0;
        int end = 0;
        for(int i = 0; i < 2*n+1; i++) {
            if(p[i]-1 > len) {
                len = p[i]-1;
                end = (i + p[i] - 1 )/2;
                
            }
        }

        return s.substr(end-len, len);
    }
};


// Two Pointer求最長回文串問題 TC:O(2* n^2) SC:O(n) 
class Solution {
public:
    string longestPalindrome(string s) {
        string ans = "";
        for(int i = 0; i < s.length(); i++){
            string s1 = palindrome(s, i, i+1); //s1去接收偶數情況字串
            string s2 = palindrome(s, i, i); // s2去接收奇數情況字串

            ans = ans.size() > s1.length() ? ans:s1;
            ans = ans.size() > s2.length() ? ans:s2;
        }
        return ans;
    }
    string palindrome(string s, int l, int r){

        while(l >= 0 && r < s.length() && s[l] == s[r]){ //防止索引越界
            // 双指针，向两边展开
            l--;
            r++;
        }
        return s.substr(l+1, r-l-1); //注意 substr用法 此意義代表l+1開始算起r-l-1個元素
    }
};

// DP TC:O(n^2) SC:O(n^2)
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,0));
        int res = 1;
        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
        }
        for(int i = 0 ; i < n-1; i++){
            if(s[i] == s[i+1]){
                dp[i][i+1] = 2;
                res = 2;
            }
        }

        

        for(int len = 3; len <= n; len++){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len - 1;
                if(s[i] == s[j] && dp[i+1][j-1] != 0){
                    dp[i][j] = dp[i+1][j-1] + 2;
                }
                res = max(res, dp[i][j]);
            }
        }

        string ret;
        bool flag = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dp[i][j] == res){
                    ret = s.substr(i, j-i+1);
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
       
        return ret;
    }
};



/*
解題思路 
求最長回文串 必須考量 長度為奇數跟偶數兩種結果
1.寫一函式判斷最長回文串
2.主函式給條件 遍歷字符串s 讓奇數跟偶數的字串長度條件都可以被遍歷到
*/
