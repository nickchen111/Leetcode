/*
934. Shortest Bridge
*/


// DFS + BFS TC:O(m*n) SC:O(m*n)
class Solution {
    int n;
public:
    int shortestBridge(vector<vector<int>>& grid) {
        n = grid.size();
        bool flag = 0;
        queue<pair<int,int>> q;
        vector<int> dirs = {0,1,0,-1,0};
        for(int i = 0; i < n && !flag; i++){
            for(int j = 0; j < n && !flag; j++){
                if(grid[i][j] == 1){
                    DFS(i,j,q, grid);
                    flag = 1;
                }
            }
        }

        int step = -1;
        
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int k = 1; k < dirs.size(); k++){
                    int nx = x + dirs[k-1];
                    int ny = y + dirs[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] == 2) continue;
                    if(grid[nx][ny] == 1) return step;
                    grid[nx][ny] = 2;
                    q.push({nx,ny});
                }
            }
        }

        return -1;
    }
    void DFS(int x, int y, queue<pair<int,int>>& q,  vector<vector<int>>& grid){
        if(x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == 0 || grid[x][y] == 2) return;
        grid[x][y] = 2;
        q.push({x,y});
        DFS(x+1, y, q, grid);
        DFS(x-1, y, q, grid);
        DFS(x, y+1, q, grid);
        DFS(x, y-1, q, grid);
    }
};

// Union find
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
            if(rootx > rooty){
                parent[rootx] = rooty;
            }
            else parent[rooty] = rootx;
        }
    };
    int n;
    vector<int> dirs = {0,1,0,-1,0};
public:
    int shortestBridge(vector<vector<int>>& grid) {
        n = grid.size();
        UF uf(n*n+1);
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    for(int t=1; t<dirs.size();t++){
                        int x = i+dirs[t-1];
                        int y = j+dirs[t];
                        if(x<0 || y<0 || x>=n || y>=n || grid[x][y] == 0) continue;
                        
                        uf.Union_(i*n+j,x*n+y);
                    }
                }
            }
        }
        int root1 = -1, root2 = -1;
        int count1 = 0; int count2 = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    if(root1 == -1){
                        count1 += 1;
                        root1 = uf.find(i*n+j);
                    }
                    else if(root2 == -1){
                        count2 += 1;
                        root2 = uf.find(i*n+j);
                    }
                    else if(root1 == uf.find(i*n+j)) count1 += 1;
                    else count2 += 1;
                }
            }
        }

        queue<pair<int,int>> q;
        if(count1 < count2){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(grid[i][j] == 1){
                        int parent = uf.find(i*n+j);
                        if(parent == root1){
                            grid[i][j] = 2;
                            q.push({i,j});
                        }
                    }
                }
            }
        }
        else {
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(grid[i][j] == 1){
                        int parent = uf.find(i*n+j);
                        if(parent == root2){
                            grid[i][j] = 2;
                            q.push({i,j});
                        }
                    }
                }
            }
        }

        int step = -1;
        while(!q.empty()){
                int sz = q.size();
                step += 1;
                while(sz--){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    for(int k = 1; k < dirs.size(); k++){
                        int nx = x + dirs[k-1];
                        int ny = y + dirs[k];
                        if(nx < 0 || ny < 0 || nx >= n || ny >= n || grid[nx][ny] == 2) continue;
                        if(grid[nx][ny] == 1) return step;
                        grid[nx][ny] = 2;
                        q.push({nx,ny});
                    }
                }
        }
        

        return -1;
    }
};

/*
只有兩座島嶼 標記成起初可能是不相連的
最少要翻轉多少個0海水讓他們相連
[0,1,0]
[0,0,0]
[0,0,1]
[0,0,1,0,1]
[0,1,1,0,1]
[0,1,0,0,1]
[0,0,0,0,0]
[0,0,0,0,0]]
這題最簡單的做法就是單就第一個遇到的島嶼加入隊列中 然後用此加入的島嶼做BFS求出最短路徑 
並且不需要union or visited數組最方便的方式就是將他在遍歷過程中改成2這個不會出現的數字代表他
*/
