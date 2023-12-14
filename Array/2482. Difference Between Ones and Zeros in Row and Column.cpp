/*
2482. Difference Between Ones and Zeros in Row and Column
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        vector<pair<int,int>> row(m,{0,0}); // 1, 0數量
        vector<pair<int,int>> col(n,{0,0});
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    row[i].first += 1;
                    col[j].first += 1;
                }
                else {
                    row[i].second += 1;
                    col[j].second += 1;
                }
            }
        }

        vector<vector<int>> res(m, vector<int>(n));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                res[i][j] = row[i].first + col[j].first - row[i].second - col[j].second;
            }
        }

        return res;
        
    }
};
