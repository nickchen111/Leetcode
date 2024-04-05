/*
1462. Course Schedule IV
*/

// 4/5
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<unordered_set<int>> next(n);
        for(auto pre : prerequisites){
            next[pre[0]].insert(pre[1]);
        }
        
        for(int i = 0; i < n; i++){
            queue<int> q;
            q.push(i);
            vector<bool> visited(n);
            
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int cur = q.front();
                    q.pop();
                    if(visited[cur]) continue;
                    visited[cur] = 1;
                    next[i].insert(cur);
                    for(auto nxt : next[cur]){
                        q.push(nxt);
                    }
                }
            }
        }

        vector<bool> res(queries.size());
        for(int i = 0; i < queries.size(); i++){
            int pre = queries[i][0]; int nxt = queries[i][1];
            if(next[pre].find(nxt) != next[pre].end()){
                res[i] = 1;
            }
        }

        return res;
    }
};


// 二維 Vector裝 答案 TC:O(n^2) SC:O(n^2)
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<vector<int>> graph(n);
        
        
        vector<vector<int>> isReachable(n, vector<int>(n));
        if(prerequisites.size() == 0) {
            vector<bool> res(queries.size(),0);
            return res;
        }

        for(auto &pre : prerequisites){
            int course = pre[0];
            int prerequisite = pre[1];
            graph[prerequisite].push_back(course);
            
        }

        
        for(int i = 0; i < n; i++){
            queue<int> q;
            q.push(i);
            vector<int> visited(n,0);
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int node = q.front();
                    q.pop();
                    if(visited[node]) continue;
                    visited[node] = 1;
                    for(auto &neighbor : graph[node]){
                        if(visited[neighbor]) continue;
                        isReachable[i][neighbor] = 1;
                        isReachable[node][neighbor] = 1;
                        q.push(neighbor);
                    }
                }
            }
        }
        
        vector<bool> res;
        for(auto & q : queries){
            int node1 = q[0], node2 = q[1];
            if(isReachable[node2][node1] == 1) res.push_back(1);
            else res.push_back(0);
        }
     
        

        return res;
    }
};

//Topological TC:O(n^2) SC:O(n)
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<unordered_set<int>> next(n);//相等於graph
        vector<unordered_set<int>> preset(n);   
        vector<int> indegree(n);
        if(prerequisites.size() == 0) {
            vector<bool> res(queries.size(),0);
            return res;
        }

        for(auto &pre : prerequisites){
            indegree[pre[1]] += 1;
            next[pre[0]].insert(pre[1]);// need to take 0 for 1
        }

        queue<int> q;
        for(int i = 0; i < n; i++){
            preset[i].insert(i);
            if(indegree[i] == 0) q.push(i);
        }

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int cur = q.front();
                q.pop();
                for(auto &neighbor : next[cur]){
                    for(auto x : preset[cur]){
                        preset[neighbor].insert(x);
                    }
                    indegree[neighbor] -= 1;
                    if(indegree[neighbor] == 0) q.push(neighbor);
                }
            }
        }

        vector<bool> res;

        for(auto &q : queries){
            int node1 = q[0],  node2 = q[1];
            res.push_back(preset[q[1]].find(q[0]) != preset[q[1]].end());
        }

        return res;
    }
};


//  Hash map 裝某個課程需要哪些先修課程 TC:O(n^2) SC:O(n)
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        int n = numCourses;
        vector<vector<int>> graph(n); 
        unordered_map<int, unordered_set<int>> map;
        if(prerequisites.size() == 0) {
            vector<bool> res(queries.size(),0);
            return res;
        }
        for(auto &pre : prerequisites){
            int course = pre[0];
            int prerequisite = pre[1];
            graph[prerequisite].push_back(course);
            
        }

        
        for(int i = 0; i < n; i++){
            queue<int> q;
            q.push(i);
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int node = q.front();
                    q.pop();
                    for(auto &neighbor : graph[node]){
                        map[i].insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }

        vector<bool> res;

        for(auto &q : queries){
            int node1 = q[0],  node2 = q[1];
            if(map[node2].find(node1) != map[node2].end()){
                res.push_back(true);
            }
            else res.push_back(false);
        }

        return res;
    }
};


/*
a -> b
a -> b b -> c then a -> c
直接給你一組query要你回答 [u,v] 是否先該上 u 才能上v
true or false
map key value : take course a need to -> value
0->1 1->2 0->2
*/
