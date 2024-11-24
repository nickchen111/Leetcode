/*
3363. Find the Maximum Number of Fruits Collected
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        int res = 0;
        for(int i = 0; i < n; i++) {
            res += fruits[i][i];
        }
        // 如何提取對角線當作限制 頂多只能走到對角線
        vector<vector<int>> memo(n, vector<int>(n, -1));
        auto dfs = [&](auto&& dfs, int i, int j) -> int {
            if(j >= n || j < n - 1 - i) {
                return INT_MIN;
            }
            if(i == 0) return fruits[i][j];
            int& ret = memo[i][j];
            if(ret != -1) return ret;

            return ret =  max({dfs(dfs, i - 1, j - 1), dfs(dfs, i - 1, j), dfs(dfs, i - 1, j + 1)}) + fruits[i][j];
        };
        
        res += dfs(dfs,n-2,n-1);
        ranges::fill(memo, vector<int>(n, -1));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                fruits[j][i] = fruits[i][j];
            }
        }
        res += dfs(dfs,n-2,n-1);
        return res;
    }
};

/*
這題規定說 只能走n-1步道終點 也就是說對角線就是第一個小孩的限制路線
(0,0)第一個小孩可以走 又下 右邊 下面
(0, n-1) 他在右上 2 : 左下，下面，又下 -1,1,0,
(n-1, 0) 他在 左下 3:右上，右邊，又下
*/
