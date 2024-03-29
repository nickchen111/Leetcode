/*
1466. Reorder Routes to Make All Paths Lead to the City Zero
*/

// BFS 3/29
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        
        vector<bool> visited(n);
        vector<vector<int>> graph(n);
        unordered_map<int, unordered_set<int>> map; // 紀錄誰指向自己
        for(auto connect : connections){
            map[connect[1]].insert(connect[0]);
            graph[connect[0]].push_back(connect[1]);
            graph[connect[1]].push_back(connect[0]);
        }

        queue<int> q;
        q.push(0);
        int res = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto next : graph[cur]){
                    if(visited[next]) continue;
                    if(map[cur].find(next) == map[cur].end()) res ++;
                    q.push(next);
                }
            }
        }

        return res; 
    }
};

// DFS TC:O(V+E) SC:O(V)
class Solution {
    vector<bool> visited;
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int,int>>> graph(n);
        visited.resize(n);
        for(const auto& con : connections){
            graph[con[0]].push_back({con[1],1});
            graph[con[1]].push_back({con[0],-1});
        }

        int res = 0;
        DFS(graph, res,0);

        return res;
    }
    void DFS(vector<vector<pair<int,int>>>& graph, int& res, int curCity){
        visited[curCity] = 1;
        for(const auto& neighbor : graph[curCity]){
            if(!visited[neighbor.first]){
                if(neighbor.second == 1) res += 1;
                DFS(graph, res, neighbor.first);
            }
        }
    }
};

// BFS 
class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {

        vector<vector<int>> graph(n);
        int outdegree = 0;
        unordered_map<int, unordered_set<int>> map;
        //知道鄰居數量 知道入度數量 如果不相符 那就要找誰沒指向我
        for(const auto& connect : connections){
            graph[connect[0]].push_back(connect[1]);
            graph[connect[1]].push_back(connect[0]);
            map[connect[1]].insert(connect[0]); // 0 -> 1
            if(connect[0] == 0) outdegree+=1;
        }

        // BFS
        int res = 0; // 如果附近的人沒有指向我 那我就要改他們的方向
        queue<int> q;
        q.push(0);
        vector<int> visited(n,0);
        
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            if(visited[cur] == 1) continue;
            visited[cur] = 1;
            int indegree = 0;
            for(auto neighbor : graph[cur] ){
                if(visited[neighbor]){
                    continue;
                }
                else {
                    if(map[cur].find(neighbor) == map[cur].end()){
                        indegree += 1;
                    }
                    q.push(neighbor);
                }
            }

            if(cur != 0) res += indegree;
            else res += outdegree;
            
        }

        return res;
    }
};

/*
此題給出一些directed edges 問說以目前的狀況來說 為了讓所有城市都可以到達city 0 最少需要改幾條edge方向
ob:
1. city 0 出度0 是必然的
2. edge 的話出度都是1 其餘的點入度出度平均變成0
  1 ->0
  |  
  2<-3->4
3/ 如果不是edge 那出度入度相減要等於0 如果是edge 入度為0 or 出度為 0 -> BFS
更簡單的想法是 每到一個點就去看他是可以指向零的還是沒指向0 沒指向就要＋＋ -> DFS
*/
