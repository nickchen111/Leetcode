/*
3212. Count Submatrices With Equal Frequency of X and Y
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> matrix(m, vector<int>(n));
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 'X') {
                    matrix[i][j] = 1;
                }
                else if(grid[i][j] == 'Y')  matrix[i][j] = -1;
                else matrix[i][j] = 0;
            }
        }
        
        int res = 0;
        vector<vector<int>> presum(m+1, vector<int>(n+1));
        vector<vector<int>> presumx(m+1, vector<int>(n+1));
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                presumx[i][j] = presumx[i-1][j] + presumx[i][j-1] - presumx[i-1][j-1] + (matrix[i-1][j-1] == 1);
                presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + matrix[i-1][j-1];
                if(presum[i][j] == 0 && presumx[i][j]) res += 1;
            }
        }
        
        return res;
    }
};

/*
從0,0出發
至少要有一個x, xy數量相等
x x x 
x x x 
x x x
[[".","."],["Y","X"]]
[[".","X"],[".","Y"]]
*/
