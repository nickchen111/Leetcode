/*
1631. Path With Minimum Effort
*/

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        //構建graph heights就可以代表我們的graph

        //構建dijkstra表 輸入一個點就可以知道左上角到他的最短距離 直接把dijkstra做成左上到右下
        int ans = dijkstra(heights);

        return ans;
    }

    //1.先把二維矩陣轉化為圖
    vector<vector<int>> dirs ={{0,1}, {1,0}, {0,-1},{-1,0}};

    vector<vector<int>> adj(vector<vector<int>>& heights, int x, int y){
        vector<vector<int>> neighbor;
        int m = heights.size(); int n = heights[0].size();

        for(auto dir:dirs){
            int nx = x + dir[0];
            int ny = y + dir[1];
            if(nx < 0 || ny < 0 || nx >=m || ny >= n) continue;

            neighbor.push_back({nx, ny});
        }
        return neighbor;
    }

    int dijkstra(vector<vector<int>>& heights){
        int m = heights.size(); int n = heights[0].size();
        vector<vector<int>> distfromstart(m, vector<int>(n, INT_MAX));
        distfromstart[0][0] = 0;

        //開始找從(0,0)點出發到大家的距離..二維 pair不好用
        priority_queue<state, vector<state>, comp> pq;
        pq.push(state(0,0,0));

        while(!pq.empty()){
            state cur = pq.top();
            pq.pop();
            int curx = cur.x;
            int cury = cur.y;
            int curEffortFromStart = cur.effortFromStart;

            if(curx == m-1 && cury == n-1) return curEffortFromStart;
            if(curEffortFromStart > distfromstart[curx][cury]) continue;

            for(auto neigh: adj(heights, curx, cury)){
                int nextx = neigh[0];
                int nexty = neigh[1];
                int nextEffortFromStart = max(distfromstart[curx][cury], abs(heights[curx][cury]-heights[nextx][nexty]));
                //更新dp table
                if(distfromstart[nextx][nexty] > nextEffortFromStart){
                    distfromstart[nextx][nexty] = nextEffortFromStart;
                    pq.push(state(nextx, nexty, nextEffortFromStart));
                }
            }
        }
        return -1; //正常情況不會到這裡

    }

    struct state{
        int x;
        int y;
        // 从起点 (0, 0) 到当前位置的最小体力消耗（距离）
        int effortFromStart;
        state(int x, int y, int effortFromStart){
            this->x = x;
            this->y = y;
            this-> effortFromStart =  effortFromStart;
        }
    };
    // 重寫仿函式的方式實現優先隊列的比較
    struct comp{
        bool operator()(state& a, state& b){
            return a.effortFromStart > b.effortFromStart;//最小的放在最上面
        }
    };

};

//la大 
class Solution {
public:
    // Dijkstra 算法，计算 (0, 0) 到 (m - 1, n - 1) 的最小体力消耗
    int minimumEffortPath(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        // 定义：从 (0, 0) 到 (i, j) 的最小体力消耗是 effortTo[i][j]
        vector<vector<int>> effortTo(m,vector<int>(n, INT_MAX)); // dp table 初始化为正无穷
        // base case，起点到起点的最小消耗就是 0
        effortTo[0][0] = 0;

        // 优先级队列，effortFromStart 较小的排在前面
        priority_queue<State,vector<State>,Comp> pq; // 第二个参数就是自定义语法格式，详见下方
        // 从起点 (0, 0) 开始进行 BFS
        pq.push(State(0, 0, 0));

        while (!pq.empty()) {
            State curState = pq.top();
            pq.pop();
            int curX = curState.x;
            int curY = curState.y;
            int curEffortFromStart = curState.effortFromStart;

            // 到达终点提前结束
            if (curX == m - 1 && curY == n - 1) {
                return curEffortFromStart;
            }

            if (curEffortFromStart > effortTo[curX][curY]) {
                continue;
            }
            // 将 (curX, curY) 的相邻坐标装入队列
            for (auto& neighbor : adj(heights, curX, curY)) {
                int nextX = neighbor[0];
                int nextY = neighbor[1];
                // 计算从 (curX, curY) 达到 (nextX, nextY) 的消耗
                int effortToNextNode = max(
                    effortTo[curX][curY],
                    abs(heights[curX][curY] - heights[nextX][nextY])
                );
                // 更新 dp table
                if (effortTo[nextX][nextY] > effortToNextNode) {
                    effortTo[nextX][nextY] = effortToNextNode;
                    pq.push(State(nextX, nextY, effortToNextNode));
                }
            }
        }
        // 正常情况不会达到这个 return
        return -1;
    }

    // 方向数组，上下左右的坐标偏移量
    vector<vector<int>> dirs {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // 返回坐标 (x, y) 的上下左右相邻坐标
    vector<vector<int>> adj(vector<vector<int>>& matrix, int x, int y) {
        int m = matrix.size(), n = matrix[0].size();
        // 存储相邻节点
        vector<vector<int>> neighbors;
        for (auto& dir : dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (nx >= m || nx < 0 || ny >= n || ny < 0) {
                // 索引越界
                continue;
            }
            neighbors.push_back({nx, ny});
        }
        return neighbors;
    }

    struct State {
        // 矩阵中的一个位置
        int x, y;
        // 从起点 (0, 0) 到当前位置的最小体力消耗（距离）
        int effortFromStart;

        State(int x, int y, int effortFromStart) {
            this->x = x;
            this->y = y;
            this->effortFromStart = effortFromStart;
        }
    };

    struct Comp {
        bool operator() (State& a, State& b) {
            return a.effortFromStart > b.effortFromStart;
        }
    };
};


/*
解題思路：
让你以左上角坐标为起点，以右下角坐标为终点，计算起点到终点的最短路径？Dijkstra 算法是不是可以做到？
但這題不是讓你求路徑總和權重 而是路徑差的權重最大值
tc: O((m * n) log (m * n)) sc: O(m * n)
*/


//在寫一次
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
