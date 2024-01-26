/*
1559. Detect Cycles in 2D Grid
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n));
        vector<int> dirs = {0,1,0,-1,0};
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(visited[i][j]) continue;
                queue<pair<int,int>> q; // cur, prev
                q.push({i*n+j,-1});
                char ch = grid[i][j];
                while(!q.empty()){
                    int sz = q.size();
                    while(sz--){
                        int cur = q.front().first;
                        int prev = q.front().second;
                        q.pop();
                        int x = cur/n;
                        int y = cur%n;
                        visited[x][y] = 1;
                        for(int k = 1; k < dirs.size(); k++){
                            int nx = x + dirs[k-1];
                            int ny = y + dirs[k];
                            if(nx < 0 || ny < 0 || nx >=m || ny >= n || prev == nx*n+ny || grid[nx][ny] != ch) continue;
                            if(visited[nx][ny]) return true;
                            q.push({nx*n+ny, x*n+y});
                        }
                    }
                }
            }
        }

        return false;
    }
};


/*
這題要在一個二維數組內找環
我的想法是一樣設定一個visited數組 如果遍歷過程中又遍歷到他就說明有還
但是在每一步的時候只會設限不能跟他前一個一樣以免走回頭路
*/
