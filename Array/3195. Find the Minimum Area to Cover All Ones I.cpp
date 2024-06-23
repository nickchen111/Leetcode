/*
3195. Find the Minimum Area to Cover All Ones I
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int min_x = INT_MAX;
        int min_y = INT_MAX;
        int max_x = -1;
        int max_y = -1;
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    min_x = min(min_x, i);
                    min_y = min(min_y, j);
                    max_x = max(max_x, i);
                    max_y = max(max_y, j);
                }
            }
        }
        
        int res = (max_x - min_x + 1 ) * (max_y - min_y + 1);
        return res;
        
    }
};

/*
找到最小的xy 與最大的
*/
