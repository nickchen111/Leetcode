/*
864. Shortest Path to Get All Keys
*/

// TC:O(m * n * 2^k) SC:O(m * n * 2^k)
class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        int m = grid.size(); int n = grid[0].size();
        queue<vector<int>> q;
        int count = 0;
        //30*30*2^6 在i j時有個狀態會是用集合來存他
        auto visited = vector<vector<unordered_set<int>>>(m, vector<unordered_set<int>>(n));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '@'){
                    q.push({i,j,0});
                    visited[i][j].insert(0);
                }
                else if(grid[i][j] >= 'a' && grid[i][j] <= 'f') count++;
            }
        }

        int finalState = 0;
        for(int i = 0; i<count; i++){
            finalState |= (1<<i);
        }


        vector<int> dirs = {0,1,0,-1,0};
        int step = -1;
        while(!q.empty()){
            int len = q.size();
            step++;
            while(len--){
                int x = q.front()[0];
                int y = q.front()[1];
                int state = q.front()[2];
                q.pop();

                for(int k = 1; k < dirs.size(); k++){
                    int nx = x + dirs[k-1];
                    int ny = y + dirs[k];
                    int newState = state;

                    if(nx < 0 || ny < 0 || nx >= m || ny >= n) 
                        continue;
                    if(grid[nx][ny] == '#') 
                        continue;
                    if(grid[nx][ny] >= 'A' && grid[nx][ny] <= 'F' && ((state>>(grid[nx][ny]-'A'))&1) == 0)
                        continue;
                    if(grid[nx][ny] >= 'a' && grid[nx][ny] <= 'f'){
                        newState |= (1 << (grid[nx][ny]-'a'));
                    }
                    if(visited[nx][ny].find(newState) != visited[nx][ny].end()) continue;
                    if(newState == finalState) return step+1;
                    q.push({nx, ny, newState});
                    visited[nx][ny].insert(newState);
                }
            }
        }

        return -1;
    }
};
