/*
329. Longest Increasing Path in a Matrix
*/


//DFS+memo TC:O(m*n) SC:O(m*n)
class Solution {
    vector<vector<int>> memo;
    int res = 0;
    int m,n;
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        //DFS+memo
        m = matrix.size(); n = matrix[0].size();
        memo = vector<vector<int>>(m, vector<int>(n,-1));
        

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                res = max(res,DFS(matrix, i, j));
            }
        }

        return res;
    }
    vector<int> dirs = {0,1,0,-1,0};
    int DFS(vector<vector<int>>& matrix, int x, int y){

        if(memo[x][y] != -1) return memo[x][y];
        
        int ans = 1;//萬一沒有符合的下家也會有自己的長度
        for(int i =1; i<dirs.size(); i++){
            int nx = x+dirs[i-1];
            int ny = y+dirs[i];
            if(nx < 0 || ny < 0 || nx >= m || ny >=n) continue;
            if(matrix[nx][ny] <= matrix[x][y]) continue;
            ans = max(ans, DFS(matrix,nx,ny)+1);
        }
        memo[x][y] = ans;
        return ans;
    }
};

// DP TC:O(m*n*lgmn) SC:O(m*n) 要先將數組遍歷sort從大排到小 否則worse case 從小到大遍歷 可能會遍歷m*n*m*n次 
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // DP
        int m = matrix.size(); int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n,1));//紀錄每一格最多能走多遠

        vector<pair<int, pair<int,int>>> cells;//排序數字從大到小 由大的開始遍歷 才不會最糟情況遍歷m*n*m*n次
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                cells.push_back({matrix[i][j],{i,j}});
            }
        }
        sort(cells.rbegin(),cells.rend());
        int res = 1;
        vector<int> dirs = {0,1,0,-1,0};
        for(auto cell:cells){
            int x = cell.second.first;
            int y = cell.second.second;

            for(int i  = 1; i<dirs.size(); i++){
                int nx = x+dirs[i-1];
                int ny = y+dirs[i];
                if(nx < 0 || ny < 0 || nx>=m || ny>=n) continue;
                if(matrix[nx][ny] <= matrix[x][y]) continue;
                dp[x][y] = max(dp[x][y],dp[nx][ny]+1);
            }
            res = max(res,dp[x][y]);
        }

        return res;
    }
};

