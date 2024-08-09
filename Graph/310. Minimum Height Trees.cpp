/*
310. Minimum Height Trees
*/

// Topological Sort TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        //base case n =1 or 2
        if(n == 1) return {0};
        if(n == 2) return {0,1};
        vector<vector<int>> graph(n);//紀錄關係 鄰接表
        vector<int> degree(n); //紀錄大家的入度

        for(auto edge: edges){//建立表
            int a = edge[0];
            int b = edge[1];
            graph[a].push_back(b);
            graph[b].push_back(a);// 無向圖即為雙向圖
            degree[a]++;
            degree[b]++;
        }

        //開始找葉子節點 bfs by queue
        queue<int> q;
        for(int i = 0; i < n; i++){
            if(degree[i] == 1){
                q.push(i);
            }
        }

        int count = 0;
        vector<int> visited(n);//用這個去判斷哪些點沒走過
        while(!q.empty()){
            int len = q.size();
            while(len--){
                int cur = q.front();
                q.pop();
                count++;
                visited[cur] = 1;
                for(auto x:graph[cur]){
                    degree[x]--;
                    if(degree[x] == 1){
                        q.push(x);
                    }
                }
            }
            if(count == n-1 || count == n-2) break;
        }

        vector<int> ans;
        for(int i = 0; i < n; i++){
            if(visited[i] != 1){
                ans.push_back(i);
            }
        }
        return ans;
    }
};

// Re-root DP TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
    vector<vector<int>> next;
    vector<tuple<int,int,int>> nodes;
    int maxDepth = INT_MAX;
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        next.resize(n);
        nodes.resize(n);
        if(n == 1) return {0};
        if(n == 2) return {0,1};
        
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        DFS(0, -1);
        
        reRoot(0, -1, 0);

        return res;
        
    }
    int DFS(int cur, int pa){
        int md = 0;
        int md2 = 0;
        int subroot = -1;
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            int nxtd = DFS(nxt, cur) + 1;
            if(nxtd > md){
                md2 = md;
                md = nxtd;
                subroot = nxt;
            }
            else if(nxtd > md2){
                md2 = nxtd;
            }
        }

        nodes[cur] = {md, md2, subroot};

        return md;
    }
    void reRoot(int cur, int pa, int from_up){
        auto &[max_d, max_d2, my] = nodes[cur];
        int curDepth = max(max_d, from_up);
        if(curDepth < maxDepth){
            maxDepth = curDepth;
            res.clear();
            res.push_back(cur);
        }
        else if(curDepth== maxDepth){
            res.push_back(cur);
        }

        for(auto nxt : next[cur]){
            if(pa == nxt) {
                continue;
            }
            reRoot(nxt, cur, max(from_up, (nxt == my ? max_d2:max_d)) + 1);
        }
    }
};

/*
解題思路：
此題是拓墣排序的應用去求最小的樹高度 那就代表跟一定是選中間的點 所以從葉子節點開始選 選到剩兩個或一個點的時候停止
需把題目給的關係轉成鄰接表 也需要一個表紀錄入度..
tc: o(n+m) sc: o(n)  n為節點 m為edge數

*/
