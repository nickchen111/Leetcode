/*
52. N-Queens II
*/

//tc: o(n^n * n^2) sc:o(n^n + n^2)
class Solution {
    int ans = 0;
public:
    int totalNQueens(int n) {
        vector<string> board(n, string(n, '.'));//初始化棋盤

        backtrack(board, 0);

        return ans;
    }
    void backtrack(vector<string>& board, int row){
        //結束條件
        int n = board.size();
        if(row == n){
            ans++;
            return;
        }

        for(int col=0; col < board[0].size(); col++){
            //剪枝
            if(isValid(board, row, col) == false) continue;

            board[row][col] = 'Q';
            backtrack(board, row+1); //下一行放皇后
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int col){
        int n = board[0].size();
        
        //看列column
        for(int i = row; i>=0; i--){
            if(board[i][col] == 'Q') return false;
        }

        //左上角
        for(int i =row-1, j = col-1; i>=0 && j>=0; i--,j--){
            if(board[i][j] == 'Q') return false;
        }

        //右上角
        for(int i= row-1, j=col+1; i>=0 && j<n; i--,j++){
            if(board[i][j] == 'Q') return false;
        }
        return true;
    }
};
