/*
1391. Check if There is a Valid Path in a Grid
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        if(m == 1 && n == 1) return true;
        queue<vector<int>> q;
        // -1 : non 1: up 2:down 3 : left 4 :right
        q.push({0,0,-1});
        vector<bool> visited(m*n+1);
        
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int x = q.front()[0];
                int y = q.front()[1];
                int prev = q.front()[2];
                q.pop();

                if(visited[x*n+y]) continue;
                if(x == m-1 && y == n-1){
                    if(prev == 1 &&( grid[x][y] == 5 || grid[x][y] == 6 || grid[x][y] == 2)) return true;
                    else if(prev == 3 &&( grid[x][y] == 1 || grid[x][y] == 3 || grid[x][y] == 5)) return true;
                    else return false;
                }
                visited[x*n+y] = 1;
                int nx = x, ny = y;
                int next = -1;
                if((prev == -1 || prev == 3) && grid[x][y] == 1){
                    nx = x;
                    ny = y + 1;
                    next = 3;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                if((prev == -1 || prev == 4) && grid[x][y] == 1){
                    nx = x;
                    ny = y - 1;
                    next = 4;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                
                if((prev == -1 || prev == 1) && grid[x][y] == 2){
                    nx = x + 1;
                    ny = y;
                    next = 1;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                if((prev == -1 || prev == 2) && grid[x][y] == 2){
                    nx = x - 1;
                    ny = y;
                    next = 2;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }

                if((prev == -1 || prev == 3) && grid[x][y] == 3){
                    nx = x + 1;
                    ny = y;
                    next = 1;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                if((prev == -1 || prev == 2) && grid[x][y] == 3){
                    nx = x;
                    ny = y - 1;
                    next = 4;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }

                if((prev == -1 || prev == 2) && grid[x][y] == 4){
                    nx = x;
                    ny = y + 1;
                    next = 3;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                if((prev == -1 || prev == 4) && grid[x][y] == 4){
                    nx = x + 1;
                    ny = y;
                    next = 1;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }

                if((prev == -1 || prev == 3) && grid[x][y] == 5){
                    nx = x-1;
                    ny = y;
                    next = 2;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                if((prev == -1 || prev == 1) && grid[x][y] == 5){
                    nx = x;
                    ny = y - 1;
                    next = 4;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }

                if((prev == -1 || prev == 1) && grid[x][y] == 6){
                    nx = x;
                    ny = y + 1;
                    next = 3;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }

                if((prev == -1 || prev == 4) && grid[x][y] == 6){
                    nx = x - 1;
                    ny = y;
                    next = 2;
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if(visited[nx*n+ny]) break;
                    q.push({nx,ny, next});
                }
                
            }
        }

        return false;
    }
};

/*
數字代表道路方向 問說能否從左上走到右下
grid[i][j]的數字可以引領現在的點走到某處
BFS 
1 -> 往回走: 3, 往後走 : 4
2 -> 往上走: 6 5,  每一個都紀錄感覺是一個方法 但似乎也有錯的可能 
直接紀錄上一次是往哪走
*/
