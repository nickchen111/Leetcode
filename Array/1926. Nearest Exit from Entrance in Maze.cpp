/*
1926. Nearest Exit from Entrance in Maze
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(); int n = maze[0].size();
        queue<pair<int,int>> q;
        q.push({entrance[0], entrance[1]});

        int step = 0;
        vector<int> dirs = {0,1,0,-1,0};
        vector<bool> visited(m*n+n,0);
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                if(visited[x * n + y]) continue;
                visited[x*n + y] = 1;
                
                if(x == 0 || y == 0 || x == m-1 || y == n-1) {
                    if(x == entrance[0] && y == entrance[1]) step = step;
                    else return step;
                }
                for(int i = 1; i < dirs.size(); i++){
                    int nx = x + dirs[i-1];
                    int ny = y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || maze[nx][ny] == '+') continue;
                    if(visited[nx * n + ny] == 1) continue;
                    q.push({nx,ny});
                }
            }
            step += 1;
        }

        return -1;
    }
};

/*
此題就是基本的走迷宮 走到邊界就算通過 求最短路徑 -> BFS會比較快 只要一到邊界就可以停止
1. queue : plus entrance 
2. BFS it's up down left right and count its step when we reach out the boundary with '.' return step
*/
