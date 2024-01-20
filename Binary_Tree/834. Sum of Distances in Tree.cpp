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

        sum += subtree[cur] - 1;
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

*/
