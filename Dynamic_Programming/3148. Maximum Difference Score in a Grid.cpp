/*
3148. Maximum Difference Score in a Grid
*/

// Greedy TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = INT_MIN/2;
        auto grid2 = grid;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i == 0 && j == 0) continue;
                int ans = INT_MAX/2;
                if(i-1 >= 0) ans = min(ans, grid2[i-1][j]);
                if(j-1 >= 0) ans = min(ans, grid2[i][j-1]);
                res = max(res, grid[i][j] - ans);
                grid2[i][j] = min(ans, grid[i][j]); // keep minimum value
            }
        }
        
        return res;
    }
};

// DP: DFS + Memo TC:O((m*n)*(m+n)) SC:O(m*n) -> TLE
class Solution {
    int m, n;
    int res = INT_MIN/2;
    int memo[1001][1001];
public:
    int maxScore(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                memo[i][j] = INT_MIN/2;
            }
        }
       
       
        
        DFS(grid,0,0);
        
        return res;
    }
    int DFS(vector<vector<int>>& grid, int x, int y){
        int cur = INT_MIN/2;
        if(memo[x][y] != INT_MIN/2) return memo[x][y];
        
        for(int i = x+1; i < m; i++){
            cur = max(cur, max(grid[i][y] - grid[x][y], grid[i][y] - grid[x][y]+ DFS(grid,i,y)));
        }
        
        for(int j = y+1; j < n; j++){
            cur = max(cur, max(grid[x][j] - grid[x][y], grid[x][j] - grid[x][y] + DFS(grid,x,j)));
        }
        
        memo[x][y] = cur;
        res = max(res, cur);
        
        return cur == INT_MIN/2 ? 0 : cur;
    }
};

/*
核心就是要看出 找出右下角與他左邊上面左上 差距最大的距離差就是答案，並且動態去紀錄之前的合理範圍最小值，需要再開一個數組去紀錄下一個點往回看可以看到的最小值
如果看不出這個而使用DFS + Memo 的話 每個點都要去考慮他後面的所有可能性就會是O((m*n)*(m+n))
*/
