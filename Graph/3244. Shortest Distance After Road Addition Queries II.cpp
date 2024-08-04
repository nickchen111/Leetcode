/*
3244. Shortest Distance After Road Addition Queries II
*/

// TC:O(n+m) SC:O(n)
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
            parent[x] = y;
        }
        else parent[y] = x;
    }
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        int count = n-1;
        parent.resize(n-1);

        iota(parent.begin(), parent.end(),0);
        
        vector<int> res(queries.size());
        // 也可以用有序集合做
        for(int i = 0; i < queries.size(); i++){
            int l = queries[i][0], r = queries[i][1]-1;
            int fr = find(r);
            int ul = find(l);
            // 路徑壓縮
            while(ul < r){
                union_(ul,fr);
                count -= 1;
                ul = find(ul+1);
            }
            res[i] = count;
        }

        return res;
    }
};
