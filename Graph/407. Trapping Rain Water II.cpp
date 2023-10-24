/*
407. Trapping Rain Water II
*/

// Dijkstra TC:O(m*n) SC:O(m*n)
class Solution {
    typedef vector<int> VI;//h x y
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        //Dijkstra BFS+PQ
        //用的想法是假設淹水了 每個最低的海平面當下可以潰堤進去柵欄內多少面積 不斷讓海平面升高直到沒有比他高的柵欄為止
        int m = heightMap.size();
        int n = heightMap[0].size();
        
        //先將所有周圍柵欄加進去
        priority_queue<VI,vector<VI>,greater<>> pq;
        vector<vector<int>> visited(m,vector<int>(n,0));
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(i == 0 || j == 0 || i ==m-1 || j == n-1){
                    pq.push({heightMap[i][j],i,j});
                }
            }
        }

        //開始BFS
        vector<int> dirs = {0,1,0,-1,0};
        int res = 0;
        int level = INT_MIN/2;
        while(!pq.empty()){
            int h = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();

            if(visited[x][y]) continue;
            visited[x][y] = true;
            if(level < h) level = h;
            res+=level-h;

            for(int i = 1; i<dirs.size(); i++){
                int nx = x+dirs[i-1];
                int ny = y+dirs[i];
                if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
                if(visited[nx][ny]) continue;
                pq.push({heightMap[nx][ny],nx,ny});
            }
        }
        
        return res;
    }
};
