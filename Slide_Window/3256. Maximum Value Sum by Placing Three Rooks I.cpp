/*
3256. Maximum Value Sum by Placing Three Rooks I
*/

// 最佳解 

// 次佳解 TC:O(m*m*9) SC:O(n^3)
class Solution {
    using LL = long long;
    int m, n;
    LL res = LLONG_MIN;
    vector<vector<int>> board;
    LL memo[501][501][501];
    vector<vector<pair<LL, int>>> arr;
    vector<bool> visited;
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        this -> board = board;
        m = board.size();
        n = board[0].size();
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                for(int k = 0; k <= n; k++){
                    
                    memo[i][j][k] = LLONG_MIN/2;
                    
                }
            }
        }
        
        vector<vector<pair<int,int>>> grid(m, vector<pair<int,int>>(n));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                grid[i][j].first = board[i][j];
                grid[i][j].second = j;
            }
        }
        
        arr.resize(m);
        for(int i = 0; i < m; i++){
            sort(grid[i].rbegin(), grid[i].rend());
            arr[i].resize(3);
            arr[i][0].first = grid[i][0].first;
            arr[i][0].second = grid[i][0].second;
            arr[i][1].first = grid[i][1].first;
            arr[i][1].second = grid[i][1].second;
            arr[i][2].first = grid[i][2].first;
            arr[i][2].second = grid[i][2].second;
        }
        
        visited.resize(n);
        for(int i = 0; i < m-2; i++){
            for(int j = 0; j < 3; j++){
                int col = arr[i][j].second; LL val = arr[i][j].first;
                visited[col] = 1;
                DFS(i+1, 1, col+1, 0, 0, val);
                visited[col] = 0;
            }
        }
        
        
        return res;
    }
    void DFS(int row, int count, int col1, int col2, int col3, LL sum){
        if(row == m && count < 3) return;
        
        
        if(memo[col1][col2][col3][count] > sum){
            return;
        }
        
        memo[col1][col2][col3][count] = sum;
        
        if(count == 3){
            res = max(res, sum);
            return;
        }
        
        
        for(int j = 0; j < 3; j++){
            int col = arr[row][j].second; LL val = arr[row][j].first;
            if(visited[col]) continue;
            visited[col] = 1;
            if(count == 1){
                DFS(row+1, count+1, col1, col+1, col3, sum + val);
            }
            else if(count == 2){
                DFS(row+1, count+1, col1,col2, col+1, sum + val);
            }
            visited[col] = 0;
        }    
        DFS(row+1, count, col1, col2, col3, sum);
    }
};
