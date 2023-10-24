/*
1392. Longest Happy Prefix
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    string longestPrefix(string s) {
        int n = s.size();
        vector<int> dp(n,0);
        dp[0] = 0;//絕對嚴格的自己一個不算是前後綴相等
        for(int i = 1; i<n;i++){
            int j = dp[i-1];//代表在i-1 index上有i個前綴與 在i 之前s[i-1] 擁有前後綴的數量
            while(j >=1 && s[i] != s[j]){
                j = dp[j-1];
            }
            //跳出來了要判斷一下原因
            dp[i] = j+(s[i] == s[j]);
        }

        int len = dp[n-1];
        return s.substr(0,len);
    }
};
/*
此題為KMP基礎題
預處理:dp[i] 代表the max length k s.t 從s[0:j-1]到 s[j:i] 中會有個 p[0:k-1] = p[i-k+1:i]有多少個前後綴相同的數量
*/
