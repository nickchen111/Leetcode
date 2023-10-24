/*
5. Longest Palindromic Substring
*/


//求最長回文串問題  tc: o(2* n^2) sc: o(n) 
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



/*
解題思路 
求最長回文串 必須考量 長度為奇數跟偶數兩種結果
1.寫一函式判斷最長回文串
2.主函式給條件 遍歷字符串s 讓奇數跟偶數的字串長度條件都可以被遍歷到
*/
