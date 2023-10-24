/*
743. Network Delay Time
*/

//Dijkstra 兩種做法就是延續 kruskal 跟 prim
//1. 用kruskal TC:O(ElgE) 
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //dijkstra 以起始點為主的kruskal的感覺 每次更新都是更新點與起點距離的更新
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;//dist y
        vector<bool> visited(n+1,0);
        pq.push({0,k});

        vector<vector<pair<int,int>>> graph(n+1);// x->y dist (x dist y)
        for(auto time:times){
            graph[time[0]].push_back({time[2],time[1]});
        }

        int res = 0;
        //PQ已經確保每次彈出來的點是有可能的最短距離候選人 直接用visited數組判斷是否已經走過了即可
        while(!pq.empty()){
            int dist = pq.top().first;
            int a = pq.top().second;
            pq.pop();
            if(visited[a] == 1) continue;
            visited[a] = 1;
            res = max(res, dist);

            for(auto neighbor:graph[a]){
                int b = neighbor.second;
                int nextDist = neighbor.first + dist;
                if(visited[neighbor.second]) continue;
                pq.push({nextDist, b});
            }
        }

        for(int i = 1; i<=n; i++){
            if(visited[i] == 0) return -1;
        }

        return res;
    }
};

//以prim為主寫法
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //dijkstra 用prim概念 
        unordered_map<int, vector<pair<int,int>>> graph(n+1);// x->y dist (x dist y)
        for(auto time:times){
            graph[time[0]].push_back({time[2],time[1]});
        }

        vector<bool> visited(n+1,0);
        vector<int> minDist(n+1,INT_MAX);
        minDist[k] = 0;

        for(int j =1; j<=n; j++){
            int minVal = INT_MAX;
            int minNode = -1;
            for(int i = 1; i<=n; i++){
                //找一個距離最近的
                if(!visited[i] && minDist[i] < minVal){
                    minVal = minDist[i];
                    minNode = i;
                }
            }
            //代表不會完成  找不到下個點了
            if(minNode == -1) break;
            visited[minNode] = 1;
            
            for(auto [d,nextNode]:graph[minNode]){
                minDist[nextNode] = min(minDist[nextNode], d+minDist[minNode]);
            }
        }

        int res = 0;
        for(int i = 1; i<=n; i++){
            res = max(res, minDist[i]);
        }

        return res == INT_MAX ? -1:res;
    }
};
// 10/19 
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        //dijkstra 以起始點為主的kruskal的感覺 每次更新都是更新點與起點距離的更新
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;//dist y
        vector<int> minDist(n+1,INT_MAX);
        minDist[k] = 0;
        pq.push({0,k});

        vector<vector<pair<int,int>>> graph(n+1);// x->y dist (x dist y)
        for(auto time:times){
            graph[time[0]].push_back({time[2],time[1]});
        }

        while(!pq.empty()){
            auto [dist,x] = pq.top();
            pq.pop();
            if(dist > minDist[x]) continue;

            for(auto neighbor:graph[x]){
                int next = neighbor.second;
                int nextDist = neighbor.first+minDist[x];
                if(nextDist < minDist[next]){
                    minDist[next] = nextDist;
                    pq.push({nextDist,next});
                }
            }
        }

        int res = 0;
        for(int i = 1; i<=n; i++){
            if(minDist[i] == INT_MAX) return -1;
            res = max(res, minDist[i]);
        }

        return res;

    }
};

class Solution {
    //dijkstra
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {

        //先把graph鄰接表構建出來
        vector<vector<pair<int, int>>> graph(n+1, vector<pair<int, int>>(n+1)); //因為是從1~n
        for(int i = 1; i<= n; i++){
            graph[i] = vector<pair<int, int>>();
        }
        for(auto time:times){
            int a = time[0];
            int b = time[1];
            int dist = time[2];
            graph[a].push_back({b, dist});//有向圖
        }

        //開始構建dijkstra表 從起點開始大家到起點的距離 輸入一個地方i 就可以得知距離
        vector<int> distfromstart = dijkstra(graph, k, n);

        //去找裡面的最大值就是最多要花的時間
        int ans = 0;
        for(int i = 1; i<=n; i++){
            if(distfromstart[i] == INT_MAX) return -1;
            ans = max(ans, distfromstart[i]);
        }

        return ans;
    }

    vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int k, int n){
        vector<int> distfromstart(n+1, INT_MAX);
        distfromstart[k] = 0;
        //開始想去找從k點出發大家跟我的距離為何？ bfs感濃厚 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});

        while(!pq.empty()){
            pair<int, int> cur = pq.top(); //也可以用auto [curdistfromstart, curnodeid]
            pq.pop();
            int curDistFromStart = cur.first;
            int curNodeID = cur.second;

            //這裡是會有重複走到某點的可能 如果他走到時的距離小就讓他進去run鄰居 但如果比當前走過的點到原點距離還要大那就掰
            if(curDistFromStart > distfromstart[curNodeID]) continue;

            //將目前的點他的鄰居拿出來算一算跟原點距離
            for(pair<int,int>& neighbor: graph[curNodeID]){ //可以寫成auto &[nextNodeID, weigh]
                int nextNodeID = neighbor.first;
                int distToNextNode = distfromstart[curNodeID] + neighbor.second;

                //更新dp table的概念更新distfromstart數組
                if(distfromstart[nextNodeID] > distToNextNode){
                    distfromstart[nextNodeID] = distToNextNode;
                    pq.push({distToNextNode, nextNodeID});
                }
            }
        }

        return distfromstart;
    }
};

class Solution {
    //floyd: 可用在任意兩節點最短距離 正負數權重皆可
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<int>> dp(n+1, vector<int>(n+1,INT_MAX/2));

        for(auto t:times){
            dp[t[0]][t[1]] = t[2];
        }
        for(int i = 1; i<=n; i++){
            dp[i][i] = 0;
        }

        for(int k = 1; k <=n; k++){//去看dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]) 是否會改變最小值
            for(int i = 1; i<=n; i++){
                for(int j=1; j<=n; j++){
                    dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j]);
                }
            }
        }

        int ans =0;
        for(int i = 1; i<=n;i++){
            ans = max(ans, dp[k][i]);
        }

        return ans == INT_MAX/2 ? -1:ans;
    }
};


/*
解題思路：
此題換句話說就是想求從指定的點出發 遍佈到所有點的最短路徑 且必須從此點出發 可用dijkstra or floyd

dijkstra 就是bfs 結合貪心算法 by priority queue (需確定 沒有負數權重 為加權有向圖 )
tc: ElogE. 通常情况下，如果不是稠密图，ElogE会比N^2有优势。 sc: o(v+e)

Floyd:
求两点之间的最短路径，典型的图论中的基本算法。因为代码短，容易理解，而且对于边权的值没有正数的限制。
本质就是轮遍所有的节点k看是否能对dp[i][j]的更新做贡献。即 dp[i][j] = min(dp[i][j], dp[i][k]+dp[k][j])
tc: o(n^3) sc:o(n^2)
*/
