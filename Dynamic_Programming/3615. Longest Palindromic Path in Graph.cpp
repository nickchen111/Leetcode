// TC:O(n^4 * 2^n) SC:O(n^2 * 2 ^n)
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        /*
        n = 14
        要求出最長回文串
        思路： 因為是回文串
        1. LC. 5 中心擴展法 可以n^2判斷是否是回文串
        2. n = 14 狀態壓縮DP 相鄰相關 不在乎之前走過啥 只在乎下一個點走啥 所以會是 dp[mask][x][y] 走到mask集合 下個點走x與y後還有多長的回文串長度
        */
        vector<vector<int>> g(n);
        for (auto &e : edges) {
            g[e[0]].emplace_back(e[1]);
            g[e[1]].emplace_back(e[0]);
        }
        vector memo(1 << n, vector<vector<int>>(n, vector<int>(n, -1)));
        auto dfs = [&] (this auto&& dfs, int mask, int x, int y) -> int {
            int &ret = memo[mask][x][y];
            if (ret >= 0) return ret;
            ret = 0;
            for (auto &nxt1 : g[x]) {
                if ((mask >> nxt1) & 1) continue;
                for (auto &&nxt2 : g[y]) {
                    if ((mask >> nxt2 & 1) == 0 && nxt1 != nxt2 && label[nxt1] == label[nxt2]) {
                        ret = max(ret, 2 + dfs(mask | (1 << nxt1) | (1 << nxt2), nxt1, nxt2));
                    }
                }
            }
            return ret;
        };
        int ans = 0;
        for (int i = 0; i < n; i++) {
            // odd palindrome
            ans = max(ans, dfs(1 << i, i, i) + 1);
            for (auto &nxt : g[i]) {
                if (i < nxt && label[nxt] == label[i]) {
                    ans = max(ans, dfs(1 << i | 1 << nxt, i, nxt) + 2);
                }
            }
        }
        return ans;
    }
};
