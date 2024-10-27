/*
1137. N-th Tribonacci Number
*/

// 矩陣快速冪: TC:O(lgn) SC:O(1)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int tribonacci(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        vector<vector<LL>> arr = {{1, 1,0}};
        vector<vector<LL>> m = {{1, 1, 0}, {1, 0, 1}, {1, 0, 0}};

        return multiply(arr, pow(m, n-2))[0][0];
        // vector<vector<LL>> a = multiply(arr, pow(m, n-1));
    }
    vector<vector<LL>> multiply(const vector<vector<LL>>& a, const vector<vector<LL>>& b) {
        int n = a.size();
        int m = b[0].size();
        int k = a[0].size();
        vector<vector<LL>> res(n, vector<LL>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int c = 0; c < k; c++) { 
                    res[i][j] = (res[i][j] + (LL)a[i][c] * b[c][j]);
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

// TC:O(n) SC:O(1)
class Solution {
public:
    int tribonacci(int n) {
        if(n == 0) return 0;
        if(n <= 2) return 1;

        int num1 = 0;
        int num2 = 1;
        int num3 = 1;
        int res = 0;
        for(int i = 3; i <= n; i++){
            res = num1 + num2 + num3;
            num1 = num2;
            num2 = num3;
            num3 = res;
        }

        return res;
    }
};
