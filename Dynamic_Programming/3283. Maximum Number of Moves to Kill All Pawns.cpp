/*
3283. Maximum Number of Moves to Kill All Pawns
*/

// TC:O(n^2*2^n + 50*50*n) SC:O(n*2^n)
class Solution {
    vector<pair<int,int>> dirs = {{2,1},{1,2},{2,-1},{-2,1},{-2,-1},{-1,2},{-1,-2},{1,-2}};
    vector<vector<int>> memo;
    vector<vector<vector<int>>> dist;
public:
    int maxMoves(int kx, int ky, vector<vector<int>>& positions) {
        int n = positions.size();
        dist.resize(n, vector<vector<int>>(50, vector<int>(50,-1)));
        
        // 預處理每一個兵走到50*50網格的最短路徑 O(15*50*50 = n*50*50)
        for(int i = 0; i < n; i++){
            int x = positions[i][0], y = positions[i][1];
            queue<pair<int,int>> q;
            q.push({x,y});
            int step = -1;
            while(!q.empty()){
                int sz = q.size();
                step += 1;
                while(sz--){
                    int curx = q.front().first;
                    int cury = q.front().second;
                    q.pop();
                    if(dist[i][curx][cury] != -1) continue;
                    dist[i][curx][cury] = step;
                    for(auto &dir : dirs){
                        int nx = curx + dir.first;
                        int ny = cury + dir.second;
                        if(nx < 0 || ny < 0 || nx >= 50 || ny >= 50 || dist[i][nx][ny] != -1) continue;
                        q.push({nx,ny});
                    }
                }
            }
        }
        
        // 狀態壓縮DP
        int u = (1<<n) - 1; // 目前有這麼多都還沒有人選走
        positions.push_back({kx, ky});
        memo.resize(n+1, vector<int>(1<<n,-1));
        return DFS(positions, n, u, u);
    }
    int DFS(vector<vector<int>>& positions, int i, int mask, int u){
        if(mask == 0) return 0;
        if(memo[i][mask] != -1) return memo[i][mask];
         
        int x = positions[i][0], y = positions[i][1];
        int n = positions.size();
        if(__builtin_parity(u^mask) == 0){
            // Alice的turn
            for(int j = 0; j < n; j++){
                if((mask >>j) & 1)
                    memo[i][mask] = max(memo[i][mask], DFS(positions, j, mask ^ (1<<j), u) + dist[j][x][y]);
            }
            
            return memo[i][mask];
        }
        else {
            int res = INT_MAX;
            for(int j = 0; j < n; j++){
                if((mask >>j) & 1)
                    res = min(res, DFS(positions, j, mask ^ (1<<j), u) + dist[j][x][y]);
            }
            
            return res;
        }
        
    }
};
