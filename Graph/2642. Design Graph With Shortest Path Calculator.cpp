/*
2642. Design Graph With Shortest Path Calculator
*/

// Dijkstra TC:O(ElgE) SC:O(V+E)
class Graph {
    int n;
    vector<vector<pair<int,int>>> graph; 
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        graph.resize(n);
        for(auto edge:edges){
            graph[edge[0]].push_back({edge[1],edge[2]});
        }

    }
    
    void addEdge(vector<int> edge) {
        graph[edge[0]].push_back({edge[1],edge[2]});
    }
    
    int shortestPath(int node1, int node2) {
        //node1到node2最短距離 dijkstra某點到某點最短距離
        vector<int> dist(n,INT_MAX);
        dist[node1] = 0;
        auto cmp = [](pair<int,int>& a, pair<int,int>& b){
            return a.second > b.second;
        };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq;
        pq.push({node1,0});
        while(!pq.empty()){
            auto cur = pq.top();
            int curDist = cur.second;
            int curNode = cur.first;
            pq.pop();
            if(curNode == node2) return curDist;
            if(curDist > dist[curNode]) continue;

            for(int i = 0; i < graph[curNode].size(); i++){
                int newDist = graph[curNode][i].second;
                int newNode = graph[curNode][i].first;
                int nextDist = newDist + dist[curNode];

                if(nextDist < dist[newNode]){
                    dist[newNode] = nextDist;
                    pq.push({newNode,nextDist});
                }
            }
        }

        return -1;
    }
};

// Floyd TC:O(n^3) SC:O(n^2)
class Graph {
    int dp[100][100];
    int n;
public:
    Graph(int n, vector<vector<int>>& edges) {
        this->n = n;
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                dp[i][j] = INT_MAX/3;
            }
        }
        for(int i =0; i<n; i++){
            dp[i][i] = 0;
        }
        for(auto edge:edges){
            dp[edge[0]][edge[1]] = edge[2];
        }
        
        for(int k = 0; k<n; k++){
            for(int i =0; i<n; i++){
                for(int j = 0; j<n; j++){
                    dp[i][j] = min(dp[i][j],dp[i][k]+dp[k][j]);
                }
            }
        }

    }
    
    void addEdge(vector<int> edge) {
        int a = edge[0]; int b =edge[1];
        for(int i =0; i<n; i++){
            for(int j = 0; j<n; j++){
                dp[i][j] = min(dp[i][j], dp[i][a]+edge[2]+dp[b][j]);
            }
        }
    }
    
    int shortestPath(int node1, int node2) {
        //node1到node2最短距離 dijkstra某點到某點最短距離
        return dp[node1][node2] ==INT_MAX/3 ? -1:dp[node1][node2];
    }
};
