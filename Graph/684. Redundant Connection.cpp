/*
684. Redundant Connection
*/

// union_find TC:O(n*lg*n) lg*n可以認爲是常數級別這個時間是發生在union_的時候 但因為會做空間壓縮 所以每次查找均攤下來快很多 可認為是常數級別 SC:O(n)
class Solution {
    unordered_map<int, int> parent;
    int find_(int x){
        if(x != parent[x]){
            parent[x] = find_(parent[x]);
        }
        return parent[x];
    }

    void Union_(int x, int y){
        x = find_(x);
        y = find_(y);
        if(x > y){
            parent[x] = y;
        }
        else {
            parent[y] = x;
        }
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        //Union-find
        for(auto edge:edges){
            int a = edge[0];
            int b = edge[1];

            //如果沒出現過先建自己為自己的parent
            if(parent.find(a) == parent.end()){
                parent[a] = a;
            }
            if(parent.find(b) == parent.end()){
                parent[b] = b;
            }

            if(find_(a) == find_(b)) return edge;
            else Union_(a,b);
        }
        return {};
    }
};
