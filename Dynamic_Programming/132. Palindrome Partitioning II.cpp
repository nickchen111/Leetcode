/*
132. Palindrome Partitioning II
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector is_palindrome(n, vector<int>(n, true));
        for (int l = n - 2; l >= 0; l--) {
            for (int r = l + 1; r < n; r++) {
                is_palindrome[l][r] = s[l] == s[r] && is_palindrome[l + 1][r - 1];
            }
        }

        vector<int> f(n);
        for (int r = 0; r < n; r++) {
            if (is_palindrome[0][r]) {
                continue;
            }
            int res = INT_MAX;
            for (int l = 1; l <= r; l++) { // 枚舉分割位置
                if (is_palindrome[l][r]) {
                    res = min(res, f[l - 1] + 1); // 在 l-1 和 l 之間切一刀
                }
            }
            f[r] = res;
        }
        return f[n - 1];
    }
};

// 遞歸寫法
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector p_memo(n, vector<int>(n, -1));
        auto p_dfs = [&](auto &&p_dfs, int l, int r) -> bool {
            if(l >= r) return true;
            if(p_memo[l][r] != -1) return p_memo[l][r];
            return p_memo[l][r] = s[l] == s[r] ? p_dfs(p_dfs, l + 1, r - 1) : false;
        };
        vector<int> memo(n, INT_MAX);
        auto dfs = [&](auto &&dfs, int i) -> int {
            if(p_dfs(p_dfs, 0, i)) return 0;
            int &ret = memo[i];
            if(ret != INT_MAX) return ret;
            // 枚舉切割點如果他不是palindrome
            for(int l = 1; l <= i; l++) {
                if(p_dfs(p_dfs, l, i)) {
                    ret = min(ret, dfs(dfs, l-1) + 1);
                }
            }
            return ret;
        };
        return dfs(dfs, n-1);
    }
};

/*
這題想求出一個字串最少可以切割成幾份讓所有substring皆是回文串
一樣可以用dp求解 先用區間dp方法求出每個區間是否是回文串 減少每次都要判斷的時間
在用n^2的方式去切割出所有的可能性 dp[i]定義成切割到i這裡為止最少需要切割出多少的字串能使他為回文串
*/
