/*
3203. Find Minimum Diameter After Merging Two Trees
*/

// TC:O(m+n) SC:O(m+n)
class Solution {
    int cand2 = 0;
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int m = edges1.size()+1;
        int n = edges2.size()+1;
        
        vector<vector<int>> graph1(m);
        vector<vector<int>> graph2(n);
        vector<int> indegree1(m);
        vector<int> indegree2(n);
        for(auto edge : edges1){
            indegree1[edge[0]] += 1;
            indegree1[edge[1]] += 1;
        }
        for(auto edge : edges2){
            indegree2[edge[0]] += 1;
            indegree2[edge[1]] += 1;
        }


        for(auto edge : edges1){
            graph1[edge[0]].push_back(edge[1]);
            graph1[edge[1]].push_back(edge[0]);
        }
        for(auto edge : edges2){
            graph2[edge[0]].push_back(edge[1]);
            graph2[edge[1]].push_back(edge[0]);
        }

        int cand1 = check(edges1,graph1, indegree1) + check(edges2,graph2, indegree2) + 1;
        auto t1 = BFS(graph1, 0);
        auto t2 = BFS(graph1, t1.first);
        cand2 = max(cand2, t2.second);
        auto t3 = BFS(graph2, 0);
        auto t4 = BFS(graph2, t3.first);
        cand2 = max(cand2, t4.second);
       
        return max(cand1, cand2);
    }
    pair<int,int> BFS(vector<vector<int>>& graph, int cur){
        int n = graph.size()+1;

        queue<int> q;
        q.push(cur);
        vector<int> dis(n,-1);
        dis[cur] = 0;
        while(!q.empty()){
            int t = q.front();
            q.pop();
            for(auto iter = graph[t].begin(); iter != graph[t].end(); iter++){
                int w = *iter;
                if (dis[w] == -1) 
                { 
                    q.push(w);   
                    dis[w] = dis[t] + 1; 
                } 
            }
        }

        int maxDis = 0; 
        int nodeIdx = 0; 
          
        for (int i = 0; i < n; i++) 
        { 
            if (dis[i] > maxDis) 
            { 
                maxDis = dis[i]; 
                nodeIdx = i; 
            } 
        } 
        return make_pair(nodeIdx, maxDis);
    }
    
    int check(vector<vector<int>>& edges, vector<vector<int>>& graph, vector<int>& indegree){
        int n = edges.size()+1;
        if(n == 1) return 0;
        
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indegree[i] == 1) q.push(i);
        }

        int depth = -1;
        int count = 0;
        vector<bool> visited(n);
        bool flag = 0;
        
        while(!q.empty()){
            int sz = q.size();
            depth += 1;
            if(q.size() % 2 == 0) flag = 1;
            else flag = 0;
            while(sz--){
                int cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto nxt : graph[cur]){
                    if(visited[nxt]) continue;
                    indegree[nxt] -= 1;
                    if(indegree[nxt] == 1) q.push(nxt);
                }
            }
        }

        
        return depth + flag;
    }
};

// 樹形DP
class Solution {
    int cand2 = 0;
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int m = edges1.size()+1;
        int n = edges2.size()+1;
        
        vector<vector<int>> graph1(m);
        vector<vector<int>> graph2(n);
        vector<int> indegree1(m);
        vector<int> indegree2(n);
        for(auto edge : edges1){
            indegree1[edge[0]] += 1;
            indegree1[edge[1]] += 1;
        }
        for(auto edge : edges2){
            indegree2[edge[0]] += 1;
            indegree2[edge[1]] += 1;
        }


        for(auto edge : edges1){
            graph1[edge[0]].push_back(edge[1]);
            graph1[edge[1]].push_back(edge[0]);
        }
        for(auto edge : edges2){
            graph2[edge[0]].push_back(edge[1]);
            graph2[edge[1]].push_back(edge[0]);
        }

        int cand1 = check(edges1,graph1, indegree1) + check(edges2,graph2, indegree2) + 1;
        DFS(graph1, 0, -1);
        DFS(graph2, 0, -1);
        
       
        return max(cand1, cand2);
    }
    

    int DFS(vector<vector<int>>& graph, int cur, int prev){
        int max_len = 0;
        for(auto nxt : graph[cur]){
            if(nxt != prev){
                int sub_len = DFS(graph, nxt, cur) + 1;
                cand2 = max(cand2, max_len + sub_len);
                max_len = max(max_len, sub_len); 
            }
        }

        return max_len;
    }
    
    int check(vector<vector<int>>& edges, vector<vector<int>>& graph, vector<int>& indegree){
        int n = edges.size()+1;
        if(n == 1) return 0;
        
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(indegree[i] == 1) q.push(i);
        }

        int depth = -1;
        int count = 0;
        vector<bool> visited(n);
        bool flag = 0;
        
        while(!q.empty()){
            int sz = q.size();
            depth += 1;
            if(q.size() % 2 == 0) flag = 1;
            else flag = 0;
            while(sz--){
                int cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto nxt : graph[cur]){
                    if(visited[nxt]) continue;
                    indegree[nxt] -= 1;
                    if(indegree[nxt] == 1) q.push(nxt);
                }
            }
        }

        
        return depth + flag;
    }
};

/*
將各點與其他點的最遠距離求出 找兩個最小的相加即為答案+1 
並且要考慮自己這棵樹本身的最大直徑
*/
