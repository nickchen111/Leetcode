/*
1977. Number of Ways to Separate Numbers
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfCombinations(string num) {
        int n = num.size();
        if(num[0] == '0') return 0;
        vector<vector<int>>presum(n+2, vector<int>(n+2));
        vector<vector<int>>lcs(n+2, vector<int>(n+2));

        for(int i = n-1; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                if(num[i] == num[j]){
                    lcs[i][j] = lcs[i+1][j+1] + 1; // 計算這兩個點開頭的最長公共字串長度
                }
                else lcs[i][j] = 0;
            }
        }
        
        for(int i = 0; i < n; i++){
            for(int len = 1; len <= i+1; len++){
                int j = i - len + 1; // 當前段的頭
                LL dp = 0;
                if(num[j] == '0') {
                    dp = 0;
                }
                else if(len == i+1){
                    dp = 1;
                }
                else {
                    int maxLen2 = min(len, j);// 當前段的長度 vs 剩下段的長度 選較少的 不可能前面只剩一點還要求他要很長
                    if(len==maxLen2 && lcs[j-maxLen2][j]<len && num[j-maxLen2+lcs[j-maxLen2][j]]>num[j+lcs[j-maxLen2][j]]){
                        maxLen2--;
                    }

                    while (maxLen2 >= 1 && num[j-maxLen2]=='0')
                        maxLen2--;

                    if(maxLen2 >= 1){
                        dp = presum[j-1][maxLen2];
                    }
                }

                presum[i][len] = (presum[i][len-1] + dp) % M; 
            }
        }

        
        return presum[n-1][n];
    }
};

/*
單調遞增 且每個數字不會有leading zero
n = 3500 -> 10^3
dp[i] 走到i位置的時候有多少種分割方案 
因為3500^2 大概是10^7 有點危
1. 如果往前合併的數字位數已經超過後面的位數 就會直接停下來
dp[i][j] 定義成走到i為止 他如果想要組成j位數 跟前面可以配對的方式
dp[i][1] = dp[i-1][1] + dp[i-1][0];
dp[i][2] = dp[i-2][2] + dp[i-2][1] + dp[i-2][0];
dp[i][3] = dp[i-3][3] + dp[i-3][2] + dp[i-3][1] + dp[i-3][0];

數字太大要怎麼去比大小!? 字串比大小嗎? -> LCS 去快速定位到該比的位置 所以需要預處理
*/ 
