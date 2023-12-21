/*
2466. Count Ways To Build Good Strings
*/

// TC: O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        
        vector<int> dp(high+1);
        int minLen = min(zero, one);
        dp[0]= 1;
        LL res = 0;

        for(int i = minLen; i <= high; i++){       
            dp[i] += ((i - zero >= 0 ? dp[i-zero] : 0 ) + (i - one >= 0 ? dp[i-one] : 0)) % M;      
            if(i >= low) res = (res + dp[i]) % M;
        }

      

        return res;
    }
};

// TC:O(n*2) SC:O(2*n)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        
        vector<vector<int>> dp(high+1, vector<int>(2,0));
        int minLen = min(zero, one);
        dp[0][0] = 0;
        dp[0][1] = 0;
        dp[zero][0] = 1;
        dp[one][1] = 1;
        for(int i = minLen; i <= high; i++){
            for(int j = 0; j < 2; j++){
                if(j == 0){
                    if(i-zero >= 0) dp[i][j] += (dp[i-zero][0] + dp[i-zero][1])%M;
                
                }
                if(j == 1){
                    if(i-one >= 0) dp[i][j] += (dp[i-one][0] + dp[i-one][1])%M;
                   
                }
            }
        }

        LL res = 0;
        for(int i = low; i <= high; i++){
            res = (res + dp[i][0] + dp[i][1]) % M;
        }

        return res;
    }
};

/*
給定你一組字串上下限長度
以及每次想加入 0 or 1 最少需加入幾個 問說能組成和法長度的可能性
dp[i][j] 目前長度是i 的狀態 以 j結尾的可能性
res = dp[low][0 or 1] ~ dp[high][0 or 1]
也可以寫成一維的 畢竟也不用考慮前面到底是 1 or 0
*/
