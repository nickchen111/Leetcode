/*
2973. Find Number of Coins to Place in Tree Nodes
*/

// TC:O(n*klgk) k atmost 5 SC:O(n + k)
class Solution {
    using LL = long long;
    vector<int> subtree[20005]; // 每顆子樹的root 都含有哪些需要的最大最小值
    vector<vector<int>> graph;
    vector<LL> res;
public:
    vector<long long> placedCoins(vector<vector<int>>& edges, vector<int>& cost) {
        int n = cost.size();
        graph.resize(n);
        res.resize(n);

        for(auto & edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);//因為不確定 root是誰 每條路線都要確保
        }

        
        DFS(0,-1,cost);

        return res;

    }

    void DFS(int cur, int parent, vector<int>& cost){

        vector<LL> arr;
        for(int next : graph[cur]){
            if(next == parent) continue;
            //這樣就有了所有子樹的資訊
            DFS(next,cur,cost);
            //那些子樹有的cost 最多五項
            for(auto x : subtree[next]){
                arr.push_back(x);
            }
        }
        //將自己也加進去
        arr.push_back(cost[cur]);
        int n = arr.size();
        sort(arr.begin(), arr.end());

        if(n < 3) res[cur] = 1;
        else {
            res[cur] = max(0LL, max(arr[n-1]*arr[n-2]*arr[n-3], arr[0]*arr[1]*arr[n-1]));
        }

        if(n >= 1) subtree[cur].push_back(arr[0]);
        if(n >= 2) subtree[cur].push_back(arr[1]);
        if(n >= 3) subtree[cur].push_back(arr[n-1]);
        if(n >= 4) subtree[cur].push_back(arr[n-2]);
        if(n >= 5) subtree[cur].push_back(arr[n-3]);

    }
};

/*
此題要你ASSIGN硬幣 
如果某個節點子數數量小於3 assign 1
如果超過1 assign 他的子節點最大那個數乘積 如果乘積 < 0 就給他0
1. three larest positive
2. two negative + one positive
3. all are neative
這些數字在什麼情況下可以加入 從子節點加回母節點 不用全部的數字都往上傳回
arr[0] : n >= 1
arr[1] : n >= 2
arr[n-1] : n >= 3
arr[n-2] : n >= 4
arr[n-3] : n >= 5
*/
