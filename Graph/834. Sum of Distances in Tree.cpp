/*
834. Sum of Distances in Tree
*/

//TC:O(n)->均攤可以變O(1) SC:O(n)
class Solution {
    vector<int> res;
    int visited[30005];
    vector<int> next[30005];
    int subtree[30005];
    int n;
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        this->n = n;
        res.resize(n);
        for(auto edge:edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        //先將所有subtree size算出來
        visited[0] = 1;
        DFS(0);

        for(int i = 1; i<n; i++){
            visited[i] = 0;
        }

        //將所有點到root距離算出
        res[0] = DFS2(0);
        
        for(int i = 1; i<n; i++){
            visited[i] = 0;
        }
        //開始計算所有點當root的跟各點距離
        DFS3(0);

        return res;
    }

    //conpute subtree size
    int DFS(int cur){
        int sum = 1;
        for(auto x:next[cur]){
            if(visited[x]) continue;
            visited[x] = 1;
            sum+=DFS(x);
        }
        subtree[cur] = sum;
        return sum;
    }
    int DFS2(int cur){
        int sum = 0;
        for(auto x:next[cur]){
            if(visited[x]) continue;
            visited[x] = 1;
            sum+=DFS2(x);
        }
        sum += subtree[cur]-1;//自己不包含在內
        return sum;
    }
    void DFS3(int cur){
        
        for(auto x:next[cur]){
            if(visited[x]) continue;
            visited[x] = 1;
            int b = subtree[x];
            int a = n-b;
            res[x] = res[cur] + a - b;
            DFS3(x);
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
