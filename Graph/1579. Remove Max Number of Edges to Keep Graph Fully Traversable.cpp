/*
1579. Remove Max Number of Edges to Keep Graph Fully Traversable
*/

// TC:O(n) SC:O(n)
class Solution {
    int parent[100005];
    int parent0[100005]; // for bob
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x > y) parent[x] = y;
        else parent[y] = x;
    }
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }

        int count0 = 0, count1 = 0, count2 = 0;
        vector<vector<int>> edge1;
        vector<vector<int>> edge2;
        for(auto edge : edges){
            int a = edge[1];
            int b = edge[2];
            if(edge[0] == 3){
                if(find(a) != find(b)){
                    union_(a, b);
                    count0 += 1;
                }
            }
            else if(edge[0] == 1){
                edge1.push_back({a,b});
                edge1.push_back({b,a});
            }
            else {
                edge2.push_back({a,b});
                edge2.push_back({b,a});
            }
        }

        memcpy(parent0, parent, sizeof(parent));// dest source, size

        for(auto edge : edge1){
            int a = edge[0];
            int b = edge[1]; 
            if(find(a) != find(b)){
                union_(a, b);
                count1 += 1;
            }
        }
        if(count0 + count1 < n-1) return -1;
        memcpy(parent, parent0, sizeof(parent));
        for(auto edge : edge2){
            int a = edge[0];
            int b = edge[1];
            if(find(a) != find(b)){
                union_(a, b);
                count2 += 1;
            }
        }

        if(count0 + count2 < n-1) return -1;

        return (int)edges.size() - count0 - count1 - count2;
    }
};
