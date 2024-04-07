/*
3108. Minimum Cost Walk in Weighted Graph
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> parent;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }
        
        return parent[x];
    }
    
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x < y){
            parent[y] = x;
        }
        else parent[x] = y;
    }
    
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        
        for(int i = 0; i < n; i++){
            parent.push_back(i);
        }
        
        for(auto e : edges){
            if(parent[e[0]]!= parent[e[1]]){
                union_(e[0],e[1]);
            }
        }
        
        unordered_map<int,int> map; // root -> val
        for(auto e : edges){
            int a = e[0], b = e[1];
            int root = find(a);
            if(map.find(root) == map.end()){
                map[root] = e[2];
            }
            else {
                int cur = map[root];
                cur &= e[2];
                map[root] = cur;
            }
        }
        
        vector<int> res(query.size());
        for(int i = 0; i < query.size(); i++){
            int a = query[i][0], b = query[i][1];
            if(a == b) continue;
            else if(find(a) != find(b)){
                res[i] = -1;
            }
            else {
                int root = find(a);
                res[i] = map[root];
            }
        }
        
        return res;
    }
};

/*
從某點走到某點 bit & 最小值 並且重複的點可以重複走
給一組query 算出每點的距離最小值
走越多路 數值可以降的越多 代表用union方式將所有可以互通的放在一起 & 所有點除了自己本身&的值 如果互通那就是此集合&的結果
001
110
*/
