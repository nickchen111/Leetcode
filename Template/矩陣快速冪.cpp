using LL = long long;
vector<vector<LL>> start = {{1, 1, 1, 1, 1}};
vector<vector<LL>> base = {{1, 1}, {1, 0}};
vector<vector<LL>> a = multiply(start, pow(base, n-1));

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
