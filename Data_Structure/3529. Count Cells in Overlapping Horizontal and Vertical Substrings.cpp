// TC:O(m * n + k) SC:O(m * n + k)
class Solution {
public:
    int countCells(vector<vector<char>>& grid, string pattern) {
        int m = grid.size(), n = grid[0].size();
        int N = m * n, L = pattern.size();
        if (L > N) return 0;
        string S;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                S.push_back(grid[i][j]);
        string T;
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++)
                T.push_back(grid[i][j]);
        auto preprocessor = [&](const string &p) {
            vector<int> lsp(L, 0);
            for (int i = 1; i < L; i++) {
                int j = lsp[i-1];
                while (j > 0 && p[i] != p[j]) j = lsp[j-1];
                lsp[i] = j + (p[i] == p[j]);
            }
            return lsp;
        };
        auto kmpSearch = [&](const string &s, const string &p, const vector<int> &lsp) {
            vector<int> res;
            int N = s.size(), L = p.size();
            vector<int> dp(N);
            dp[0] = (s[0] == p[0]);
            if (dp[0] == L) res.push_back(0 - L + 1);
            for (int i = 1; i < N; i++) {
                int j = dp[i-1];
                while (j > 0 && s[i] != p[j]) j = lsp[j-1];
                dp[i] = j + (s[i] == p[j]);
                if (dp[i] == L) {
                    res.push_back(i - L + 1); 
                }
            }
            return res;
        };
        auto lsp = preprocessor(pattern);
        auto hor = kmpSearch(S, pattern, lsp);
        auto ver = kmpSearch(T, pattern, lsp);
        vector<int> horDiff(N+1, 0), verDiff(N+1, 0);
        for (int st : hor) {
            horDiff[st] += 1;
            horDiff[st+L] -= 1;
        }
        for (int st : ver) {
            verDiff[st] += 1;
            verDiff[st+L] -= 1;
        }
        vector<int> horCover(N, 0), verCover(N, 0);
        for (int i = 0, acc = 0; i < N; i++) {
            acc += horDiff[i];
            horCover[i] = (acc > 0);
        }
        for (int i = 0, acc = 0; i < N; i++) {
            acc += verDiff[i];
            verCover[i] = (acc > 0);
        }
        int ans = 0;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int si = r * n + c;
                int ti = c * m + r;
                if (horCover[si] && verCover[ti]) ans++;
            }
        }
        return ans;
    }
};
