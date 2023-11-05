/*
2603. Collect Coins in a Tree
*/


// TC:O(V+E) SC:O(V*E)
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<unordered_set<int>> next(n);//用此結構是為了方便刪除
        vector<int> indegree(n);
        for(auto edge:edges){
            next[edge[0]].insert(edge[1]);
            next[edge[1]].insert(edge[0]);
            indegree[edge[0]]+=1;
            indegree[edge[1]]+=1;
        }

        //開始做剪枝
        queue<int> q;
        for(int i = 0; i<n; i++){
            if(indegree[i] == 1 && coins[i] == 0) q.push(i);
        }

        vector<int> deleted(n,0);
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                int cur = q.front();
                q.pop();
                deleted[cur] = 1;
                for(auto nxt:next[cur]){
                    indegree[nxt]-=1;
                    next[nxt].erase(cur);//方便不會再走回頭路
                    if(indegree[nxt] == 1 && coins[nxt] == 0) q.push(nxt); 
                }
            }
        }

        //開始賦予深度 depth <=2 的都不列入路徑
        vector<int> depth(n,-1);
        for(int i = 0; i<n; i++){
            if(indegree[i] == 1 && deleted[i] == 0){
                q.push(i);
                depth[i] = 1;
            }
        }

        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                int cur = q.front();
                q.pop();
                for(auto nxt:next[cur]){
                    indegree[nxt]-=1;
                    next[nxt].erase(cur);
                    depth[nxt] = max(depth[nxt],depth[cur]+1);
                    if(indegree[nxt] == 1) q.push(nxt);
                }
            }
        }

        int m = 0;
        for(int i = 0; i<n; i++){
            if(depth[i] >= 3) m+=1;
        }

        if(m > 0) return (m-1)*2;
        else return 0;
    }
};

/*
此題想求將所有硬幣取光最少需要走幾步
條件有二
1.可以隔空取硬幣 可以隔空取兩步的硬幣
2.從任意點出發 但是最後還是需要返回此點 
第二個條件其實是假命題 因為不論選取哪個點最後都是看edge數量*2的步數 因為想要走回原出發點

解決此題需要想到要將沒有硬幣的徒勞的path避免掉 以及去對節點標深度
*/
