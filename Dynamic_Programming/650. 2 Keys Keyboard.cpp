/*
650. 2 Keys Keyboard
*/

//我的寫法 可整除再去做判斷 直接用可整除的那個數 TC:O(n^2) SC:O(n)
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n+1,INT_MAX/2);
        dp[1] = 0;

        for(int i = 2; i<=n; i++){
            for(int j = 1; j<i; j++){
                if(i%j == 0)
                    dp[i] = min(dp[i], dp[j]+((i-j)/j)+1);
            }
        }

        return dp[n];
    }
};

//優化寫法 結合類似貪心的思想 整除完最大的那個數 用此數去copy paste somehow 會得到最少次數的copy paste
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n+1,INT_MAX/2);
        dp[1] = 0;

        for(int i = 2; i<=n; i++){
            for(int j = 2; j<=i; j++){
                if(i%j != 0) continue;
                int k = i/j;
                dp[i] = min(dp[i], dp[k]+1+j-1);
                break;
            }
        }

        return dp[n];
    }
};

// "此題去思考什麼樣的情況會可以得到最多的Ａ
// dp[i] 定義為最少要操作幾次才能得到i個A
// if(i % j == 0)
// dp[6] = dp[2]+(i-j)/j+1 or dp[1] +(i-j)/j+1 or dp[3] +(i-j)/j+1"
