/*
459. Repeated Substring Pattern
*/

// KMP TC:O(n) SC:O(n)
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        //KMP
        int n = s.size();
        vector<int> dp(n,0);
        dp[0] = 0;
        for(int i = 1;i<n; i++){
            int j = dp[i-1];
            while(j > 0 && s[i] != s[j]){
                j = dp[j-1];
            }
            dp[i] = j+(s[i] == s[j]);
        }
        int k = dp[n-1];

        return (k>0 && n%(n-k) == 0);
    }
};

// brute force TC:O(n^2) SC:O(n)
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        for(int len = 1; len<=n/2; len++){
            if(n%len == 0){
                string substring = s.substr(0,len);
                string res = "";
                for(int i = 0; i<n/len; i++){
                    res+=substring;
                }
                if(res == s) return true;
            }
        }

        return false;
    }       
};
/*
KMP 此題還是蠻難想到要這樣做的
尾巴和n-k個的元素相同 後綴又和前綴相同 一直過去如果數目能夠整除的話就是代表為repeated substring pattern
[***][***][___]
[___][***][***]
              n-1
*/
