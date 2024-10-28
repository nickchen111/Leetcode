/*
1220. Count Vowels Permutation
*/

// 矩陣快速冪 TC:O(lgn) SC:O(1)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int countVowelPermutation(int n) {
        vector<vector<LL>> start = {{1, 1, 1, 1, 1}};
        vector<vector<LL>> base = {{0,1,0,0,0}, {1,0,1,0,0}, {1,1,0,1,1}, {0,0,1,0,1}, {1,0,0,0,0}};
        vector<vector<LL>> a = multiply(start, pow(base, n-1));
        int res = 0;
        for(LL &x : a[0]) {
            res = (res + x) % MOD;
        }

        return res;
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

//TC:O(n) SC:O(5*n)
class Solution {
public:
    int countVowelPermutation(int n) {
        vector<vector<long>> dp(n,vector<long>(5,0));
        long long M = 1e9+7;
        for(int j = 0; j<5; j++){
            dp[n-1][j] = 1;
        }

        for(int i = n-2; i>=0; i--){
            dp[i][0] = dp[i+1][1];
            dp[i][1] = (dp[i+1][0]+dp[i+1][2])%M;
            dp[i][2] = (dp[i+1][0]+dp[i+1][1]+dp[i+1][3]+dp[i+1][4])%M;
            dp[i][3] = (dp[i+1][2]+dp[i+1][4])%M;
            dp[i][4] = dp[i+1][0];
        }


        long res = 0;
        for(int j = 0; j<5; j++){
            res = (res+dp[0][j])%M;
        }

        return res;
    }
};

// TC:O(n) SC:O(10)
class Solution {
public:
    int countVowelPermutation(int n) {
        //優化空間
        vector<long> dp(5,0);
        long long M = 1e9+7;
        for(int j = 0; j<5; j++){
            dp[j] = 1;
        }

        for(int i = n-2; i>=0; i--){
            auto dp_temp = dp;
            dp[0] = dp_temp[1];
            dp[1] = (dp_temp[0]+dp_temp[2])%M;
            dp[2] = (dp_temp[0]+dp_temp[1]+dp_temp[3]+dp_temp[4])%M;
            dp[3] = (dp_temp[2]+dp_temp[4])%M;
            dp[4] = dp_temp[0];
        }


        long res = 0;
        for(int j = 0; j<5; j++){
            res = (res+dp[j])%M;
        }

        return res;
    }
};

/*
dp[i][0] = how many strings of [i:n-1] can be formed s[i] = a
dp[i][1] = how many strings of [i:n-1] can be formed s[i] = e
...
0:a
1:e
2:i
3:o
4:u

*/
