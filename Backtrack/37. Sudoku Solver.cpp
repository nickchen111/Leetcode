/*
37. Sudoku Solver
*/

//backtrack TC:O(N^9) N為空格的格子數量 此為完全窮舉的複雜度 實際上不會那麼多 SC:O(Ｎ)
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        
        backtrack(board, 0, 0);
    }

    bool backtrack(vector<vector<char>>& board, int i, int j){
        if(i == 9) return true; //backtrack寫成bool形式 這樣一旦有正確寫法就會終止backtrack
        if(j == 9) return backtrack(board, i+1, 0); //換一行繼續窮舉

        if(board[i][j] != '.') return backtrack(board, i, j+1);//代表已經有規定的字元

        for(char ch = '1'; ch<='9'; ch++){
            if(!isValid(board, i, j, ch)) continue;
            board[i][j] = ch;
            if(backtrack(board, i, j+1) == true) return true;
            board[i][j] = '.';
        }

        return false;
    }

    bool isValid(vector<vector<char>>& board, int i, int j, char ch){
        //數獨三種情況

        //看不同row
        for(int row = 0; row<9; row++){
            if(row != i && board[row][j] == ch) return false;
        }

        //看不同column
        for(int col = 0; col<9; col++){
            if(col != j && board[i][col] == ch) return false;
        }

        //看自己格子內是否已經存在此數字
        //找出格子最左上那格
        int x = i/3*3;
        int y = j/3*3;
        for(int k = 0; k<3; k++)
            for(int p = 0; p<3; p++)
                if(board[x+k][y+p] == ch) return false;
        
        return true;
    }
};
/*
此題就是暴力窮舉所有可能
然後需去另外判斷可能的合法性 -> isValid?
*/
