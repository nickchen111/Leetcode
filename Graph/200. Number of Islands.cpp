/*
200. Number of Islands
*/



class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for(int y = 0; y < m; ++y){
            for(int x = 0; x < n; ++x){
                ans += grid[y][x] - '0'; //將grid 字串轉成int
                dfs(grid, x, y, m, n);
            }
        }
        return ans;
    }
private:
    void dfs(vector<vector<char>>& grid, int x, int y, int m, int n){
        if(x<0 || y<0 || x>=n || y>= m || grid[y][x] == '0') //grid 這一項一定要放在後面 不然會先判讀到會有runtine error
            return;
        grid[y][x] = '0';
        dfs(grid, x+1, y, m, n);
        dfs(grid, x-1, y, m, n);
        dfs(grid, x, y+1, m, n);
        dfs(grid, x, y-1, m, n);
    }
};

//第二種寫法改一下ans那邊
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for(int y = 0; y < m; ++y){
            for(int x = 0; x < n; ++x){
                if(grid[y][x] == '1'){ //   加上if 只看等於1的地方
                dfs(grid, x, y, m, n);
                ans++;
                }
            }
        }
        return ans;
    }
private:
    void dfs(vector<vector<char>>& grid, int x, int y, int m, int n){
        if(x<0 || y<0 || x>=n || y>= m || grid[y][x] == '0') //先邊界在無效值grid 這一項一定要放在後面 不然會先判讀到會有runtine error 或者可以改成！＝1
            return;
        grid[y][x] = '0';
        dfs(grid, x+1, y, m, n);
        dfs(grid, x-1, y, m, n);
        dfs(grid, x, y+1, m, n);
        dfs(grid, x, y-1, m, n);
    }
};
