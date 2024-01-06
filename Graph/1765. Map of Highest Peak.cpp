/*
1765. Map of Highest Peak
*/

// TC:O(m*n) SC:O(m*n/2)
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size();
        int n = isWater[0].size();
        vector<vector<int>> res(m, vector<int>(n));
        vector<vector<int>> visited(m,vector<int>(n));
        queue<pair<int,int>> q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(isWater[i][j] == 1) {
                    res[i][j] = 0;
                    q.push({i,j});
                    visited[i][j] = 1;
                }
                else res[i][j] = -1;
            }
        }

        int step = 0;
        vector<int> dirs = {0,1,0,-1,0};
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int i = 1; i < dirs.size(); i++){
                    int nx = x + dirs[i-1];
                    int ny = y + dirs[i];
                    if(nx < 0 || ny < 0 || nx >= m || ny >= n || visited[nx][ny]) continue;
                    visited[nx][ny] = 1;
                    res[nx][ny] = step;
                    q.push({nx,ny});
                }
            }
        }

        return res;
    }
};


/*
0:代表水 1: 代表陸地
請返回題目規定合法的每個地的高度 並且盡量最大化高度
海水高度必定是0 兩個cell高度差不能超過1
如果旁邊都是海水陸地可以是1就好 
這題我的想法是都先將海水高度填好 然後將每個海水加入queue裏面
並且開始擴展 慢慢加一
*/
