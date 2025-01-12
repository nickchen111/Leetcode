// TC:O(m*n) SC:O(1)
class Solution {
public:
    vector<int> zigzagTraversal(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        vector<int> result;
        bool goingRight = true; 
    
        for (int i = 0; i < m; i++) {
            if (goingRight) {
                for (int j = 0; j < n; j++) {
                    if ((i + j) % 2 == 0) {
                        result.push_back(grid[i][j]);
                    }
                }
            } else {
                for (int j = n - 1; j >= 0; j--) {
                    
                    if ((i + j) % 2 == 0) {
                        result.push_back(grid[i][j]);
                    }
                }
            }
            goingRight = !goingRight;
        }
        
        return result;
    }
};
