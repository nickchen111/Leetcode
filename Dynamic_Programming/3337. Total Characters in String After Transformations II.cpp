/*
3337. Total Characters in String After Transformations II
*/

// TC:O(m*m + m^3 * lgt) t = 最多10^9次數, m 為字母數量26 SC:O(26^2)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int lengthAfterTransformations(string s, int t, vector<int>& nums) {
        vector<vector<LL>> start(1, vector<LL>(26));
        for(auto &ch : s) {
            start[0][ch-'a'] += 1;
        }
        int n = nums.size();
        vector<vector<LL>> base(n, vector<LL>(n));
        // f[i][j] 交換次數為i時，字母為j的狀況會有的長度 = f[i-1][(j+1) % 26] + f[i-1][(j+2) % 26]
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j <= i + nums[i]; j++) {
                base[i][j%26] = 1;
            }
        }

        vector<vector<LL>> a = multiply(start, pow(base, t));
        LL res = 0;
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
