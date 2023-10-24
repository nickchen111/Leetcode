/*
210. Course Schedule II

*/

//DFS  TC: O(V+E) SC:O(V+E)
class Solution1 {
public:
    vector<bool> visited;
    vector<bool> onpath;
    bool hascycle = false;
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        visited = vector<bool>(numCourses, false);
        onpath = vector<bool>(numCourses, false);
        vector<int> postorder;
        //vector<int> ans; 這項其實不需要
        auto graph = buildgraph(numCourses, prerequisites);
        for(int i=0; i<numCourses; i++){ //開始遍歷graph
            traverse(graph, postorder, i);
        }
        if(hascycle) return {};
        reverse(postorder.begin(), postorder.end());

        return postorder;
    }
    vector<vector<int>> buildgraph(int numCourses, vector<vector<int>>& prerequisites){
        vector<vector<int>> graph(numCourses, vector<int>(0));

        for(auto edge:prerequisites){
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to);
        }
        return graph;
    }
    void traverse(vector<vector<int>>& graph, vector<int>& postorder, int s){
        if(onpath[s] == true){
            hascycle = true;
        }
        if(visited[s] || hascycle) return;

        visited[s] = true;
        onpath[s] = true;
        //前序遍歷的位置
        for(auto x:graph[s]){
            traverse(graph, postorder, x);
        }//瘋狂遍歷到最深處
        postorder.push_back(s); //postorder容器來收割成果
        onpath[s] = false;
    }
};
/*
解題思路
這題是dag + topological sort
dag的話就是要檢查有沒有環
要檢查一個graph有沒有環可以用bfs/dfs去遍歷 如果同一條遍歷的路徑上遇到已經標記過為true的點 就代表有環
topological sort的話可以將我後序遍歷的結果reverse就是答案了  後序遍歷的特性就是左右會先放 如果按照被依賴的關係即那些超難專業科目會先被放到sort裡面所以要reverse

1.先將graph創建起來
2.為了要遍歷所以要有visited onpath兩個來配合判斷有沒有環
3.在主函式創建一堆ans postorder graph以及初始化visited onpath等等雜事
3.要去traverse 函數裡面需要有後序遍歷將答案放進創建的容器裡
最後在main function要記得reverse即為解答
*/

//BFS TC:O(V+E) SC:O(V+E)
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        //BFS
        vector<int> res;
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses);
        for(auto p:prerequisites){
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]+=1;
        }

        queue<int> q;
        for(int i = 0; i<numCourses; i++){
            if(indegree[i] == 0) q.push(i);
        }
    
        while(!q.empty()){
            int cur = q.front();
            res.push_back(cur);
            q.pop();
            for(auto neighbor:graph[cur]){
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) q.push(neighbor);
            }
        }

        if(res.size() == numCourses) return res;
        else return {};
    }
};
