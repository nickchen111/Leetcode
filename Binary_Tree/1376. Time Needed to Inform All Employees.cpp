/*
1376. Time Needed to Inform All Employees
*/

// BFS TC:O(n) SC:O(n)
class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        if(n == 1) return 0;
        vector<vector<int>> graph(n);
        for(int i = 0; i < n; i++){
            if(manager[i] == -1) continue;
            graph[manager[i]].push_back(i);
        }

        queue<pair<int,int>> q;
        q.push({headID,0});
        int res = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto [curID, cumTime]= q.front();
                q.pop();
                if(graph[curID].size() > 0){
                    for(auto &employee: graph[curID]) q.push({employee, cumTime + informTime[curID]});
                }
                else res = max(res, cumTime);
            }
        }

        return res;
    }
};

// DFS
class Solution {
    int res = 0;
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        if(n == 1) return 0;
        vector<vector<int>> graph(n);
        for(int i = 0; i < n; i++){
            if(manager[i] == -1) continue;
            graph[manager[i]].push_back(i);
        }

        DFS(graph, headID, 0, informTime);

        return res;
    }
    void DFS(vector<vector<int>>& graph, int curID, int cumTime, vector<int>& informTime){
        if(graph[curID].size() == 0){
            res = max(res, cumTime);
            return;
        }

        for(auto &employee: graph[curID]){
            DFS(graph, employee, cumTime + informTime[curID], informTime);
        }
    }
};


/*
此題把公司組織變成tree 說要從CEO開始下達命令給他的下屬  ．．．問這中間所需時間為多少
ps: 在這之間 某一層傳遞的時間不需要累加＝＝
headID 是根
從head ID 出發看他有哪些勤勉地員工 找到以後乘上你各位的info time 
*/
