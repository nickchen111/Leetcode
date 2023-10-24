/*
64. Minimum Path Sum
*/


//此題用dp才是最好的解 但其實也可以套用dijkstra or floyd來解這題 因為同樣是求兩點最短距離

//dijkstra TC:(m*n*lgn) SC:O(m*n)
class Solution {
public:
    struct state{
        int x;
        int y;
        int dist;
        state(int x, int y, int dist){
            this->dist = dist;
            this->y = y;
            this->x = x;
        }

        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
    int minPathSum(vector<vector<int>>& grid) {
        //grid 算是他們的加權
        int m = grid.size(); int n = grid[0].size();

        //計算出每個點到起點的最短距離
        vector<vector<int>> mindist(m, vector<int>(n, INT_MAX));
        mindist[0][0] = grid[0][0];
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state(0,0,grid[0][0]));

        //bfs
        while(!pq.empty()){
            state cur = pq.top(); pq.pop();
            int curx = cur.x;
            int cury = cur.y;
            int curDist = cur.dist;

            if(curDist > mindist[curx][cury]) continue;
            if(cur.x == m-1 && cur.y == n-1) return curDist;

            for(auto adj: neighbor(grid, curx, cury)){
                int Nextx = adj[0];
                int Nexty = adj[1];
                int NextDist = mindist[curx][cury] + grid[Nextx][Nexty];
                if(NextDist <  mindist[Nextx][Nexty]){
                    mindist[Nextx][Nexty] = NextDist;
                    pq.push(state(Nextx,Nexty,NextDist));
                }
            }
        }
        return mindist[m-1][n-1];//到不了！？
    }

    vector<vector<int>> dirs = {{1,0},{0,1}};//不是往下就是往右
    vector<vector<int>> neighbor(vector<vector<int>>& grid, int x, int y){
        int m = grid.size(); int n = grid[0].size();
        vector<vector<int>> res;
        for(auto dir:dirs){
            int nx = x+dir[0];
            int ny = y+dir[1];
            if(nx >=m || ny >=n) continue;
            res.push_back({nx,ny});
        }

        return res;
    }
};

/*
最小路徑和：
感覺可以用dijkstra or floyd
*/
