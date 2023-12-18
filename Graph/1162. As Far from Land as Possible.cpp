/*
1162. As Far from Land as Possible
*/

// TC:O(n*n) SC:O(n)
class Solution {
    int m,n;
    int res = -1;
public:
    int maxDistance(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        vector<int> dirs = {0,1,0,-1,0}; 
        queue<pair<int,int>> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                   q.push({i,j});
                   grid[i][j] = 2;
                }
            }
        }

        int step = -1;
        int res = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int k = 1; k < dirs.size(); k++){
                    int nx = x + dirs[k-1];
                    int ny = y + dirs[k];
                    if(nx < 0 || ny < 0 || nx >=m || ny >= n) continue;
                    if(grid[nx][ny] == 2) continue;
                    if(grid[nx][ny] == 0){
                        res = max(res, step + 1);
                        grid[nx][ny] = 2;
                        q.push({nx,ny});
                    }
                }
            }
        }


        return res;
    }  
    
};

/*
1代表陸地 0代表海水 想問n*n圖中1 0 相差最遠是多遠 都只能找最近的
如果沒有 1 or 0 return -1
n = 100 都找看看就是100*100 固定一個0 去找最近的1
但是這題給太多0了 需要思維轉換成 從 1 開始找 找離他最遠的 答案會是離所有1最遠的0 
那就所有的1都開始遍歷最後剩下的0就會自動被更新成答案
*/
