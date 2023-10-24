/*
778. Swim in Rising Water
*/

// BFS + PQ TC:O(n^2*lgn) SC:O(n^2)
class Solution {
    typedef vector<int> VI;// h x y
public:
    int swimInWater(vector<vector<int>>& grid) {
        //BFS+PQ 類似dj的感覺
        int n = grid.size();
        auto visited = vector<vector<int>>(n, vector<int>(n,0));

        priority_queue<VI, vector<VI>, greater<>> pq;
        pq.push({grid[0][0],0,0});

        int res = 0;
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()){
            int h = pq.top()[0];
            int x = pq.top()[1];
            int y = pq.top()[2];
            pq.pop();
            
            res = max(res, h);
            if(visited[x][y]) continue;
            if(x == n-1 && y == n-1) return res;
            visited[x][y] = true;

            for(int i = 1; i<dirs.size(); i++){
                int nx = x+dirs[i-1];
                int ny = y+dirs[i];

                if(nx<0 || ny<0 || nx>=n || ny>=n) continue;
                if(visited[nx][ny]) continue;
                pq.push({grid[nx][ny],nx,ny});
            }
        }

        return -1;

    }
};
