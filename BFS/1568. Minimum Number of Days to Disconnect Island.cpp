/*
1568. Minimum Number of Days to Disconnect Island
*/

// TC:O(m*n*m*n) SC:O(m*n)
class Solution {
    int m, n;
public:
    int minDays(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        
        int count = isIsland(grid);
        if(count >= 2 || count == 0) return 0;

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    grid[i][j] = 0;
                    int count = isIsland(grid);
                    if(count >= 2 || count == 0) return 1;
                    grid[i][j] = 1;
                }
            }
        }

        return 2;
    }
    
    int isIsland(vector<vector<int>>& grid){
        
        vector<int> dirs = {0,1,0,-1,0};
        vector<bool> visited(m*n+1); 
        int count = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 0 || visited[i*n+j]) continue;
                queue<pair<int,int>> q;
                q.push({i,j});

                while(!q.empty()){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    if(visited[x*n+y]) continue;
                    visited[x*n+y] = 1;
                    for(int k = 1; k < dirs.size(); k++){
                        int nx = x + dirs[k-1];
                        int ny = y + dirs[k];
                        if(nx < 0 || ny < 0 || nx >= m || ny >= n || grid[nx][ny] == 0 || visited[nx*n+ny]) continue;
                        q.push({nx,ny});
                    }
                }
                count += 1;
                if(count > 1) return 2;
            }
        }
        return count;
    }
};

/*
x x x
x x
x

x x x
x x x 
x x x 

[1,1,0,1,1],
[1,1,1,1,1],
[1,1,0,1,1],
[1,1,0,1,1]]
看起來難點在於要如何判斷disconnect一個區域需要做多少次
900取2 -> 450*899 = 404550種可能
30*30遍歷一波 結果是?
*/
