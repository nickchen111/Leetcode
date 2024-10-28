/*
790. Domino and Tromino Tiling
*/

// 矩陣快速冪: TC:O(lgn) SC:O(1)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numTilings(int n) {
        return f2(n-1);
    }
    int f2(int n) {
        if(n == 0) return 1;
        if(n == 1) return 2;
        if(n == 2) return 5;

        vector<vector<LL>> arr = {{5,2,1}};
        vector<vector<LL>> m = {{2,1,0}, {0,0,1},{1,0,0}};

        return multiply(arr, pow(m, n-2))[0][0];
    }
    vector<vector<LL>> multiply(const vector<vector<LL>>& a, const vector<vector<LL>>& b) {
        int n = a.size();
        int m = b[0].size();
        int k = a[0].size();
        vector<vector<LL>> res(n, vector<LL>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int c = 0; c < k; c++) { 
                    res[i][j] = (res[i][j] + (LL)a[i][c] * b[c][j]) % MOD;
                }
            }
        }
        return res;
    }

    vector<vector<LL>> pow(vector<vector<LL>>& m, int p) {
        int n = m.size();
        vector<vector<LL>> res(n, vector<LL>(n));
        for (int i = 0; i < n; i++) {
            res[i][i] = 1; // 單位矩陣
        }

        for(; p != 0; p >>= 1) {
            if(p & 1) {
                res = multiply(res, m);
            }
            m = multiply(m, m);
        }
        return res;
    }
};

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
