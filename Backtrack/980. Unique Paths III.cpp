/*
980. Unique Paths III
*/

// TC:O(4^mn) SC:O(mn)
class Solution {
    int res = 0;
    int m,n;
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int startx = -1;
        int starty = -1;
        int count = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    startx = i;
                    starty = j;
                }
                else if(grid[i][j] == 0) count += 1;
            }
        }

       
        grid[startx][starty] = -1;
        DFS(startx+1, starty, grid,0,count);
        DFS(startx, starty+1, grid,0,count);
        DFS(startx-1, starty, grid,0,count);
        DFS(startx, starty-1, grid,0,count);

        return res;
    }
    void DFS(int x, int y, vector<vector<int>> grid, int sum, int count){
        if(x < 0 || y < 0 || x >= m || y >= n  || grid[x][y] == -1) return;
        
        if(grid[x][y] == 2){
            if(count == sum) res += 1;
            return;
        }
        grid[x][y] = -1;
        DFS(x+1, y, grid,sum+1,count);
        DFS(x, y+1, grid,sum+1,count);
        DFS(x-1, y, grid,sum+1,count);
        DFS(x, y-1, grid,sum+1,count);
    }
};

/*
從起點走到終點的方式有幾種 並且每一個不是障礙物的都要走過一次
20*20*4*20*20 = 640000 也可以過
*/
