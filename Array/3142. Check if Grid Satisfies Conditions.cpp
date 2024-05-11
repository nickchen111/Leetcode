/*
3142. Check if Grid Satisfies Conditions
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    bool satisfiesConditions(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i+1 < m){
                    if(grid[i][j] != grid[i+1][j]) return false;
                }
                if(j+1 < n){
                    if(grid[i][j] == grid[i][j+1]) return false;
                }
            }
        }
        
        return true;
    }
};
/*
grid[i][j] == grid[i + 1][j] (if it exists).
grid[i][j] != grid[i][j + 1] (if it exists).
*/
