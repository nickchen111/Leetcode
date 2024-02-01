/*
2266. Count Number of Texts
*/

// TC:O(4*n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countTexts(string s) {
        int n = s.size();
        
        vector<LL> dp(n+1); // 切割起來當前連續狀態能構造出多少種可能
        dp[0] = 1;
        
        for(int i = 0; i < n; i++){
            dp[i+1] = dp[i];
            if(i > 0){
                if(s[i] == '7' || s[i] == '9'){
                    for(int j = i-1; j >= max(0,i-3); j--){
                        if(s[i] == s[j]){
                            dp[i+1] = (dp[i+1] + dp[j]) % M;
                        }
                        else break;
                    }
                }
                else {
                    for(int j = i-1; j >= max(0,i-2); j--){
                        if(s[i] == s[j]){
                            dp[i+1] = (dp[i+1] + dp[j]) % M;
                        }
                        else break;
                    }
                }
            }
        }

        
        return dp[n];
    }
};


/*
79是4種可能其他都是3種
22233 -> 每個數字頂多往回看前四個
2222 -> 4+2+1 = 7; 用加法原理加起來
每次都先從上一個狀態繼承過來 然後再開始判斷跟之前的是否一樣 就可以加入先前的先前一個
x x x x x   
*/
