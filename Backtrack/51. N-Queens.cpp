/*
51. N-Queens
*/


class Solution {
    vector<vector<string>> ans;
public:
    vector<vector<string>> solveNQueens(int n) {
        //去做回溯
        vector<string> board(n, string(n,'.'));

        backtrack(board, 0);
        return ans;
    }

    void backtrack(vector<string>& board, int row){
        //固定row來放皇后
        //結束條件 base case
        
        if(row == board.size()){
            ans.push_back(board);
            return;
        }

        for(int col = 0; col < board[0].size(); col++){//column數 可選擇 取名col 更順眼
            if(!isValid(board, row, col)) continue;

            board[row][col] = 'Q';
            backtrack(board, row+1);
            board[row][col] = '.';
        }
    }

    bool isValid(vector<string>& board, int row, int column){
        int n = board[0].size();
        //檢查左上

        for(int i = row-1, j = column-1; j>=0 && i >=0; i--,j--){
            if(board[i][j] == 'Q') return false;
        }

        //檢查右上
        for(int i = row-1, j = column+1; i>=0 && j<n; i--, j++){
            if(board[i][j] == 'Q') return false;
        }

        //檢查column
        for(int i = row; i >= 0; i--){
            if(board[i][column] == 'Q') return false;
        }
        return true;
    }
};

/*
tc: o(n^n * n^2) 但實際上不會到這麼多因為有isValid剪枝 sc: o(n^2 + n^n)
空間複雜度主要來自存儲答案的ans數組，這個數組的大小取決於有多少合法的解，最壞情況下是O(n^n)。這是因為在最壞情況下，每一行都有n種可能的放置皇后的方式。
另外，也需要一個二維數組board來表示棋盤，空間複雜度是O(n^2)。
總的空間複雜度是O(n^n + n^2)，主要是由ans和board所占用的空間決定。 但也一樣不會到這麼多
*/
