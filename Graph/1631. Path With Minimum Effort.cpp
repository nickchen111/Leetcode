/*
1631. Path With Minimum Effort
*/

// 用visited 數組 先彈出來的肯定是最優秀的路徑 TC: O((m * n) log (m * n)) SC: O(m * n)
class Solution {
    struct state{
        int a, b, dist;
        state(int dist, int a, int b){
            this -> a = a;
            this -> b = b;
            this -> dist = dist;
        }
        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        // BFS
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state{0,0,0});

        vector<bool> visited(m*n+1);
       
        vector<int> dirs = {0,1,0,-1,0};
        
        while(!pq.empty()){
            int x = pq.top().a;
            int y = pq.top().b;
            int dist = pq.top().dist;
            pq.pop();

            if(x == m-1 && y == n-1) return dist;
            if(visited[x*n+y]) continue;
            visited[x*n+y] = 1;
            for(int i = 1; i < dirs.size(); i++){
                int nx = x + dirs[i-1];
                int ny = y + dirs[i];
                if(nx < 0 || ny < 0 || nx >= m || ny >= n || visited[nx*n+ny]) continue;
                int nextDist = max(dist, abs(heights[x][y] - heights[nx][ny]));
                pq.push({nextDist, nx, ny});
                
            }
        }
        
        return -1;
        
    }
};

// Dijkstra + prim概念的minDist TC: O((m * n) log (m * n)) SC: O(m * n)
class Solution {
    struct state{
        int a, b, dist;
        state(int dist, int a, int b){
            this -> a = a;
            this -> b = b;
            this -> dist = dist;
        }
        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        // BFS
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state{0,0,0});

        vector<int> minDist(m*n+1, INT_MAX);
        minDist[0] = 0;
        vector<int> dirs = {0,1,0,-1,0};
        
        while(!pq.empty()){
            int x = pq.top().a;
            int y = pq.top().b;
            int dist = pq.top().dist;
            pq.pop();

            if(x == m-1 && y == n-1) return dist;
            if(dist > minDist[x*n+y]) continue;

            for(int i = 1; i < dirs.size(); i++){
                int nx = x + dirs[i-1];
                int ny = y + dirs[i];
                if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                int nextDist = max(minDist[x*n+y], abs(heights[x][y] - heights[nx][ny]));
                if(nextDist < minDist[nx*n+ny]){
                    minDist[nx*n+ny] = nextDist;
                    pq.push({nextDist,nx,ny});
                }
                
            }
        }
        
        return -1;
        
    }
};

/*
解題思路：
让你以左上角坐标为起点，以右下角坐标为终点，计算起点到终点的最短路径？Dijkstra 算法是不是可以做到？
但這題不是讓你求路徑總和權重 而是路徑差的權重最大值
tc: O((m * n) log (m * n)) sc: O(m * n)
*/


// old_type 2023.08
class Solution {
public:
    // Dijkstra 算法，计算 (0, 0) 到 (m - 1, n - 1) 的最小体力消耗
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(); int n = heights[0].size();
        //建構dijkstra 
        vector<vector<int>> EffortTo(m, vector<int>(n, INT_MAX));
        EffortTo[0][0] = 0;
        //想一下dijkstra 本質是什麼？ 是bfs 結合貪心算法搭配priority queue... 
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state{0,0,0});

        while(!pq.empty()){
            state cur = pq.top();
            pq.pop();
            int curx = cur.x;
            int cury = cur.y;
            int curEffortFromStart = cur.effortToStart;

            if(curEffortFromStart > EffortTo[curx][cury]) continue; //代表這個路徑不好不屑走

            //終止條件在此 當curx cury走到終點
            if(cur.x == m-1 && cur.y == n-1) return curEffortFromStart;

            //還沒走到 尋訪他的鄰居
            for(auto &neighbor:adj(heights, curx, cury)){
                int nextx = neighbor[0];
                int nexty = neighbor[1];
                int effortToNextNode = max(EffortTo[curx][cury], abs(heights[curx][cury] - heights[nextx][nexty]));

                //畢竟也有可能已經走過了
                if(EffortTo[nextx][nexty] > effortToNextNode){
                    EffortTo[nextx][nexty] = effortToNextNode;
                    pq.push(state{nextx, nexty, effortToNextNode});
                }
            }
        }
        return -1;
    
    }
    //先把二維的選擇規劃出來
    vector<vector<int>> dirs = {{0,1},{1,0}, {0, -1},{-1,0}};
    vector<vector<int>> adj(vector<vector<int>>& heights, int x, int y){

        int m = heights.size(); int n = heights[0].size();
        vector<vector<int>> neighbor;
        for(auto dir:dirs){
            int nx = x + dir[0];
            int ny = y + dir[1];
            
            if(nx < 0 || ny < 0 || nx >= m || ny>=n) continue;

            neighbor.push_back({nx, ny});
        }
        return neighbor;
    }

    struct state{
        int x;
        int y;
        int effortToStart;
        state(int x, int y, int effortToStart){
            this->x = x;
            this->y = y;
            this-> effortToStart =  effortToStart;
        }
        //透過重載實現優先隊列比較
        bool operator> (const state &other) const{ // greater = '>' 加const priority queue.top()才會返回你啊
            return effortToStart > other.effortToStart;
        }
    };
};
