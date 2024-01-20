/*
834. Sum of Distances in Tree
*/

// TC:O(n) SC:O(n)
class Solution {
    int subtree[30005];
    vector<int> res;
    vector<int> graph[30005];
    int n;
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        this -> n = n;
        res.resize(n);
        for(auto &edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        DFS1(0,-1); // 計算所有節點當root有多少節點

        res[0] = DFS2(0,-1); // 先算好從0開始走需要的答案

        DFS3(0,-1);
        return res;
        
    }
    int DFS1(int cur, int parent){
        int sum = 1; 
        for(auto x : graph[cur]){
            if(x == parent) continue;
            sum += DFS1(x, cur);
        }

        subtree[cur] = sum;
        return sum;
    }
    int DFS2(int cur, int parent){
        int sum = 0;
        for(auto x : graph[cur]){
            if(x == parent) continue;
            sum += DFS2(x, cur);
        }

        sum += subtree[cur] - 1; // 自己不包含在內 因為leaf node 後面沒有node了 不會貢獻任何路徑
        return sum;
    }
    void DFS3(int cur, int parent){
        
        for(auto x : graph[cur]){
            if(x == parent) continue;
            int b = subtree[x];
            int a = n - b;
            res[x] = res[cur] + a - b;
            DFS3(x, cur);
        }
    }
};

/*
此題用到一個經典的概念re-root
0.pick the root
1. compute subtree-size of every node
2. compute f(root)-> distance sum toward root 也是遞歸思想 要算出他的子數作為根後子數所有孩子到子根距離 再加上他全部的孩子  
3. compute f(node)-> f(root) + a - b -> f(root)+n-2b
*/
