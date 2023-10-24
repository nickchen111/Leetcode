/*
1091. Shortest Path in Binary Matrix
*/

//BFS TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        if(grid[0][0] == 1 || grid[m-1][n-1] == 1) return -1;

        vector<vector<bool>> visited(m,vector<bool>(n,0));

        queue<pair<int, int>> q;
        int path = 1;
        q.push({0,0});
        visited[0][0] = true;

        vector<vector<int>> dirs = {{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                auto cur = q.front();
                q.pop();
                int x = cur.first;
                int y = cur.second;
                if(x == m-1 && y == n-1) return path;
                //八個方向
                for(int k = 0; k<8; k++){//int 比auto dir還快不少
                    int nx = x + dirs[k][0];
                    int ny = y + dirs[k][1];

                    if(nx>=0 && ny>=0 && nx<m && ny <n && grid[nx][ny] == 0 && !visited[nx][ny]){
                        q.push({nx,ny});
                        visited[nx][ny] = true;
                    }
                }
            }
            path++;
        }
        return -1;
    }
};

/*
此題跟752很像是一個用BFS窮舉出最短路徑的題目
*/
