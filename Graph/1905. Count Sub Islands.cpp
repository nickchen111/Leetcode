/*
1905. Count Sub Islands
*/


//DFS TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size(); int n = grid1[0].size();

        for(int i=0; i<m; i++) 
            for(int j=0; j<n; j++){
                if(grid1[i][j] == 0 && grid2[i][j] == 1) DFS(i,j,grid2);
            }

        //開始計算grid2有幾座島嶼
        int res = 0;

       for(int i=0; i<m; i++) 
            for(int j=0; j<n; j++){
                if(grid2[i][j] == 1){
                    res++;
                    DFS(i,j,grid2);
                }
            }

        return res;
    }

    void DFS(int x, int y, vector<vector<int>>& grid2){
        int m = grid2.size(); int n = grid2[0].size();

        if(x<0 || y<0 || x>=m || y>=n || grid2[x][y] == 0) return;
        grid2[x][y] = 0;
        DFS(x+1,y, grid2);
        DFS(x,y+1, grid2);
        DFS(x-1,y, grid2);
        DFS(x,y-1, grid2);
    }
};

//Union-Find TC:O(m*n) SC:O(m*n)
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
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size(); int n = grid1[0].size();

        int dummy = m*n;
        UF uf(m*n+1);
        int root = uf.find(dummy);

        for(int i = 0; i < m; i++){
            for(int j = 0; j<n; j++){
                if(grid2[i][j] == 1){
                    int cur = i*n+j;
                    if(i+1 <m && grid2[i+1][j] == 1) uf.union_((i+1)*n+j, cur);
                    if(j+1 <n && grid2[i][j+1] == 1) uf.union_(i*n+(j+1), cur);
                }
                
            }
        }
        
        //計算grid2島嶼數量
        int islandNumber = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j<n; j++){
                if(grid2[i][j] == 1){
                    if(uf.find(i*n+j) == i*n+j){
                        islandNumber++;
                    }
                }
                
            }
        }

        //排除掉grid1沒包含到的島嶼
        unordered_set<int> set; //紀錄不符合的root
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid2[i][j] == 1 && grid1[i][j] == 0 && set.find(uf.find(i*n+j)) == set.end()){
                    islandNumber--;
                    set.insert(uf.find(i*n+j));
                }
            }
        }

        return islandNumber;
    }
};

/*
此題想問說grid1中包含了幾個grid2中的島嶼 子集的概念
可以用union-find or DFS, DFS想法是 只要grid2有島嶼的地方 但是grid1卻是海水那就把grid2此點連結的全部淹掉 代表grid1不可能會包含這座島嶼

*/
