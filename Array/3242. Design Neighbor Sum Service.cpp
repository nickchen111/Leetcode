/*
3242. Design Neighbor Sum Service
*/

// TC:O(m*n) SC:O(m*n)
class neighborSum {
    vector<vector<int>> grid;
    int m, n;
public:
    neighborSum(vector<vector<int>>& grid) {
        this->grid = grid;
    }
    
    int adjacentSum(int value) {
        int sum = 0;
        int x = 0, y = 0;
        m = grid.size(); 
        n = grid[0].size();
        for(int i = 0; i < m; i++){
            bool flag = 0;
            for(int j = 0; j < n; j++){
                if(grid[i][j] == value){
                    flag = 1;
                    x = i;
                    y = j;
                    break;
                }
            }
            if(flag) break;
        }
        
        if(x-1 >= 0) sum += grid[x-1][y];
        if(y-1 >= 0) sum += grid[x][y-1];
        if(x+1 < m) sum += grid[x+1][y];
        if(y+1 < n) sum += grid[x][y+1];
        
        return sum;
    }
    
    int diagonalSum(int value) {
        int sum = 0;
        int x = 0, y = 0;
        m = grid.size(); 
        n = grid[0].size();
        for(int i = 0; i < m; i++){
            bool flag = 0;
            for(int j = 0; j < n; j++){
                if(grid[i][j] == value){
                    flag = 1;
                    x = i;
                    y = j;
                    break;
                }
            }
            if(flag) break;
        }
        
        if(x-1 >= 0 && y-1 >= 0) sum += grid[x-1][y-1];
        if(x-1 >= 0 && y+1 < n) sum += grid[x-1][y+1];
        if(x+1 < m && y-1 >= 0) sum += grid[x+1][y-1];
        if(x+1 < m && y+1 < n) sum += grid[x+1][y+1];
        
        return sum;
    }
};

/**
 * Your neighborSum object will be instantiated and called as such:
 * neighborSum* obj = new neighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */
