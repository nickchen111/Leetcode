/*
1020. Number of Enclaves
*/

//DFS TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        for(int i = 0; i<m; i++){
            if(grid[i][0] == 1) DFS(i,0,grid);
            if(grid[i][n-1] == 1) DFS(i,n-1,grid);
        }
        
        for(int j = 0; j<n; j++){
            if(grid[0][j] == 1) DFS(0,j,grid);
            if(grid[m-1][j] == 1) DFS(m-1,j,grid);
        }

        int res = 0;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1) res++;
            }
        }

        return res;

        
    }

    vector<int> dirs = {0,1,0,-1,0};
    void DFS(int x, int y, vector<vector<int>>& grid){
        int m = grid.size(); int n = grid[0].size();
        if(x < 0 || y < 0 || x>=m || y>=n || grid[x][y] == 0) return;

        grid[x][y] = 0;

        for(int i = 1; i<dirs.size(); i++){
            int nx = x+dirs[i-1];
            int ny = y+dirs[i];
            DFS(nx,ny,grid);
        }
    }
};

// Union_Find TC:O(m*n) SC:O(m*n)
class Solution {
    class UF{
        vector<int> parent;
    public:
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
        void union_(int x, int y){
            int rootx = find(x);
            int rooty = find(y);

            if(rootx != rooty) parent[rootx] = rooty;
        }

        bool isConnected(int x, int y){
            int rootx = find(x);
            int rooty = find(y);
            return rootx == rooty;
        }
    };
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        vector<int> dirs = {0,1,0,-1,0};

        UF uf(m*n+1);
        int dummy = m*n;
        for(int i = 0; i<m; i++){
            if(grid[i][0] == 1) uf.union_(i*n, dummy);
            if(grid[i][n-1] == 1) uf.union_(i*n+n-1, dummy); 
        }

        for(int j = 1; j<n; j++){
            if(grid[0][j] == 1) uf.union_(j, dummy);
            if(grid[m-1][j] == 1) uf.union_((m-1)*n+j,dummy);
        }

        //將內圈的陸地union再一起
        for(int i = 1; i<m-1; i++){
            for(int j = 1; j<n-1; j++){
                if(grid[i][j] == 1){
                    for(int dir = 1; dir<dirs.size(); dir++){
                        int nx = i+dirs[dir-1];
                        int ny = j+dirs[dir];
                        if(nx < 0 || ny < 0 || nx >=m || ny >=n) continue;
                        if(grid[nx][ny] == 1) uf.union_(i*n+j, nx*n+ny);
                    }
                }
            }
        }

        int root = uf.find(dummy);
        int res = 0;
        for(int i = 1; i<m-1; i++){
            for(int j = 1; j<n-1; j++){
                if(uf.find(i*n+j) != root && grid[i][j] == 1) res++;
            }
        }

        return res;
    }
};
