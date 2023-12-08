/*
2318. Number of Distinct Roll Sequences
*/

// TC:O(6*6*6*n) SC:O(n*6*6)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    LL dp[10001][7][7];
public:
    int distinctSequences(int n) {
        if(n == 1) return 6;

        LL count = 0; //處理 n == 2狀況
        for(int a = 1; a <= 6; a++){
            for(int b = 1; b <= 6; b++){
                if(a != b && gcd(a,b) == 1){
                    dp[2][a][b] = 1;
                    count = (count + dp[2][a][b])%M;
                }
            }
        }
        if(n == 2) return count;

        for(int i = 3; i <= n; i++){
            for(int a = 1; a <= 6; a++){
                for(int b = 1; b <= 6; b++){
                    if(a == b || gcd(a,b) > 1) continue;
                    for(int c = 1; c <= 6; c++){
                        if(c != a){
                            dp[i][b][a] += dp[i-1][c][b];
                            dp[i][b][a] %= M;
                        }
                    }
                }
            }
        }

        LL res = 0;
        for(int a = 1; a <= 6; a++){
            for(int b = 1; b <= 6; b++){
                res = (res + dp[n][a][b])%M;
            }
        }

        return res;
    }
};

/*
擲骰子
GCD = 1
1. 相鄰兩元素不能相同
2. 橫跨的一個元素也不能相同
 X X X X X X X 
         c b a
1. b != a
2. gcd(b,a) == 1
3. c != a
dp[i][b][a] = dp[i-1][c][b] 缺什麼補什麼
*/
