/*
790. Domino and Tromino Tiling
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int numTilings(int n) {
        long M = 1e9+7;
        vector<vector<long>> dp(n+1, vector<long>(2,0));
        dp[0][0] = 1;
        dp[1][0] = 1;
        for(int i = 2; i <= n; i++){
            dp[i][0] = (dp[i-1][0] + dp[i-2][0] + 2*dp[i-1][1]) % M;
            dp[i][1] = (dp[i-2][0] + dp[i-1][1]) % M;
        }

        return dp[n][0];
    }
};

/*
這題算是蠻特別的fibonacci幾何dp題 問說給你一個n能夠用tri or domino 拼出2*n的幾何圖形的方式有幾種
下手點還是先思考單純domino狀況 會發現它就是fibonacchi 之後要再考慮三個的形狀要怎麼接上
對應這種題目就要用他可以接上的形狀去思考 所以就是一開始平滑的接面接上他dp[i-2][0] or 原本就有凸出一塊
這種狀況只要多接一個2即可 然後有分凸上面凸下面 對應這題兩種狀況的拼湊數量會一樣所以紀錄一個狀態即可 
2 x n
for 2
dp[1] = 1;
dp[2] = 2;
dp[3] = dp[2] + dp[1] = 3;
dp[4] = 5 ?

*/
