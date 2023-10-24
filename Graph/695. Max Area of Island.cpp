/*
695. Max Area of Island
*/

//DFS TC:O(m*n) SC:O(m*n)
class Solution { 
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        int res = 0;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1){
                    res = max(res, calculateArea(i,j,grid));
                }
            }
        }

        return res;
    }

    int calculateArea(int x, int y, vector<vector<int>>& grid){
        int m = grid.size(); int n = grid[0].size();
        if(x<0 || y<0 || x>=m ||y>=n || grid[x][y] == 0) return 0;
        grid[x][y] = 0;

        return calculateArea(x+1, y, grid) + calculateArea(x, y+1, grid) + calculateArea(x-1, y, grid) + calculateArea(x, y-1, grid)+1;
    }
};

//Union-Find TC:O(m*n) SC:O(m*n)
class Solution {
    struct UF{
        vector<int> parent;
        UF(int n){
            for(int i = 0; i<n; i++){
                parent.push_back(i);
            }
        }

        int find(int x){
            if(x != parent[x]){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void Union_(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            if(rootx != rooty){
                parent[rootx] = rooty;
            }
        }
    };
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        //計算島嶼數量 by union-find
        vector<int> dirs = {0,1,0,-1,0};
        int m = grid.size(); int n = grid[0].size();
        UF uf(m*n+1);
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1){
                    for(int t=1; t<dirs.size();t++){
                        int x = i+dirs[t-1];
                        int y = j+dirs[t];
                        if(x<0 || y<0 || x>=m || y>=n || grid[x][y] == 0) continue;
                        uf.Union_(i*n+j,x*n+y);
                    }
                }
            }
        }
        unordered_map<int,int> map;
        int count = 0;
        for(int i = 0; i<m;i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1){
                    map[uf.find(i*n+j)]++;
                }
            }
        }

        for(auto x:map){
            count = max(count,x.second);
        }

        return count;
    }
};
