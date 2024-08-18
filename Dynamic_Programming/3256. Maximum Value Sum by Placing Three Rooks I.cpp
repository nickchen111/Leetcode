/*
3256. Maximum Value Sum by Placing Three Rooks I
*/

// 最佳解 

// 次佳解 TC:O(m*m*9) SC:O(n^2)
class Solution {
    using LL = long long;
    int m, n;
    LL res = LLONG_MIN/2; 
    vector<vector<int>> board;
    LL memo[101][101];
    vector<vector<pair<LL, int>>> arr;
    vector<bool> visited;
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        this -> board = board;
        m = board.size();
        n = board[0].size();
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                memo[i][j] = LLONG_MIN/2;
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
                DFS(i+1, 1, col+1, 0, val);
                visited[col] = 0;
            }
        }
        
        
        return res;
    }
    void DFS(int row, int count, int col1, int col2, LL sum){
        if(row == m && count < 3) return;
        
        if(count == 3){
            res = max(res, sum);
            return;
        }

        if(memo[col1][col2] > sum){
            return;
        }
        
        memo[col1][col2] = sum;
    
        
        
        for(int j = 0; j < 3; j++){
            int col = arr[row][j].second; LL val = arr[row][j].first;
            if(visited[col]) continue;
            visited[col] = 1;
            if(count == 1){
                DFS(row+1, count+1, col1, col+1,sum + val);
            }
            else if(count == 2){
                DFS(row+1, count+1, col1,col2, sum + val);
            }
            visited[col] = 0;
        }    
        DFS(row+1, count, col1, col2, sum);
    }
};

/*
同一個row col 只能有個rook 要放三個rooks
最多得分是多少?
100 * 2, 三個

[[95,-90,-62,-94],[62,59,-21,46],[23,24,19,9],[-79,-12,91,16]]
[[82,13,51],[-43,-96,60],[-25,70,-79],[86,37,-97],[-87,87,-87],[-67,73,6],[-80,-65,-72]]
[[-12,70,-48,-74],[-71,-75,63,-67],[-46,81,4,-86],[29,-51,-51,16]]
*/
