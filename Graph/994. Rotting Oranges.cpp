/*
994. Rotting Oranges
*/

//BFS TC:O(m*n) SC:O(m*n) 
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        //BFS
        int m = grid.size(); int n = grid[0].size();
        queue<pair<int,int>> q;
        //將所有時間為0的rotten果實加入第一次的隊列中

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 2){
                    q.push({i,j});
                }
            }
        }

        //開始計算要幾分鐘腐爛果實可以腐爛完所有可以被腐爛的果實
        vector<int> dirs ={0,1,0,-1,0};
        int minutes = -1;
        while(!q.empty()){
            int sz = q.size();
             minutes++;
            for(int i =0; i<sz; i++){
                int x=q.front().first;
                int y=q.front().second;
                q.pop();
                for(int j = 1; j<dirs.size(); j++){
                    int nx = x+dirs[j-1];
                    int ny = y+dirs[j];
                    if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
                    if(grid[nx][ny] == 0 || grid[nx][ny] == 2) continue;
                    grid[nx][ny] = 2;
                    q.push({nx,ny});
                }
            }
        }

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1) return -1;
            }
        }

        return minutes == -1 ? 0:minutes;
    }
};
