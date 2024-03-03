/*
3070. Count Submatrices with Top-Left Element and Sum Less Than k
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
    using LL = long long;
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<LL>> presum(m+1, vector<LL>(n+1));
        int count = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + grid[i-1][j-1];
                if(presum[i][j] <= k) count += 1;
            }
        }
        
        return count;
        
       
        
    }
};

/*
將所有包含最左上角的元素 並且sum為 <= k 的數量算出來
*/
