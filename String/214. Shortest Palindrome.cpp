/*
214. Shortest Palindrome
*/


//KMP TC:O(n+nlgn) SC:O(n)
class Solution {
public:
    string shortestPalindrome(string s) {
        if(s == "") return "";
        string p = s;
        reverse(s.begin(),s.end());
        //先對模式串做預處理
        vector<int> suf = preprocess(p);

        int n = s.size();
        vector<int> dp(n,0);
        dp[0] = (s[0] == p[0]);
        for(int i = 1; i<n; i++){
            int j = dp[i-1];
            while(j>0 && s[i] != p[j]){
                j = suf[j-1];
            }
            dp[i] = j+(s[i] == p[j]);
        }

        int len = dp[n-1];
        //將後面可以的擷取出來並且翻轉就會是要加上的字串
        string B = p.substr(len);
        reverse(B.begin(),B.end());
        string res = B+p;

        return res;
    }

    vector<int> preprocess(string& p){
        int n = p.size();
        vector<int> suf(n,0);
        suf[0] = 0;
        for(int i = 1; i<n; i++){
            int j = suf[i-1];
            while(j>0 && p[i] != p[j]){
                j = suf[j-1];
            }
            suf[i] = j + (p[i] == p[j]);
        }

        return suf;
    }
};


//DP TC:O(n^2) SC:O(n^2) TLE
class Solution {
public:
    string shortestPalindrome(string s) {
        //DP 此區間段是否是回文串
        if(s == "") return s;
        int n = s.size();
        vector<vector<bool>> dp(n,vector<bool>(n,0));
        //一個的狀況
        for(int i = 0; i<n; i++){
            dp[i][i] = true;
        }
        //兩個
        for(int i = 1; i<n; i++){
            if(s[i]==s[i-1])
            dp[i-1][i] = true;
        }

        for(int len = 3; len<=n; len++){
            for(int i = 0;i+len-1<n;i++){
                int j = i+len-1;
                if(s[i] == s[j] && dp[i+1][j-1]){
                    dp[i][j] = true;
                }
            }
        }

        //本身就是回文串了
        if(dp[0][n-1]) return s;

        string res;
        for(int j = n-2; j>=0;j--){
            if(dp[0][j]){
                string temp = s.substr(j+1,n-1-j);
                reverse(temp.begin(),temp.end());
                res = res+temp+s;
                break;//從後面開始一旦有後面就不需要了
            }
        }

        return res;
    }
};

/*
此題求加多少字可以讓字串變成最短回文串
兩種做法 
1.區間dp TC:O(n^2)
2.KMP
想法很巧妙 先將s倒過來
s本身會是模式串
因為我們要求的就是盡量讓s前面很多都就已經是回文串了 剩下的字元就是我們要新增在首的數量
ex: p = AA'B
    s = B'AA' 會發現p島過來變成新的字串 他的後綴就會是原本的前綴 if他們本身是回文串的話
    [abba]bcdff
    ffdcb[abba]
*/
