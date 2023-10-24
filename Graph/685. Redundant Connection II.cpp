/*
685. Redundant Connection II
*/

// Union_Find TC:O(V+E) SC:O(V)
class Solution {
    unordered_map<int,int> parent;
    int find_(int x){
        if(x != parent[x]){
            parent[x] = find_(parent[x]);
        }
        return parent[x];
    }
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        //此題從I 的無向改成有向圖 且必須符合tree 也是問該刪除哪個edge
        //有兩種可能1.發現入度為2的點 有兩個parent肯定是錯的 但不確定要刪掉哪條 2. 入度都為1 那麼就是刪掉環中任意一條邊都可以
        vector<int> cand1;
        vector<int> cand2;
        int n = edges.size();
        for(auto edge:edges){
            int a = edge[0];
            int b = edge[1];
            if(parent.find(b) != parent.end()){
                cand1 = {a,b};
                cand2 = {parent[b],b};
                break;
            }
            else parent[b] = a;
        }

        //開始找是否有環 by Union_Find
        for(int i = 1; i<=n; i++){
            parent[i] = i;
        }

        for(auto edge:edges){
            if(edge == cand1) continue;//任意取一個來看是否就沒環了
            
            int a = edge[0];
            int b = edge[1];
            if(find_(a) != find_(b)){
                parent[b] = a;
            }
            else{
                if(cand2.size() == 0) return edge;//當下此為環的一部分
                else return cand2;//cand1 pass還是有環 那就是cand2該刪除
            }
        }
        return cand1;
    }
};

/*
   1
  2 3
     4
    x
    7->5
        
*/
