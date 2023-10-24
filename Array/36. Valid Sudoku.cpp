/*
36. Valid Sudoku
*/

// 用類似hash map概念紀錄遍歷過的每行每列都有什麼數字 遍歷過就定值為1 
//TC:O(m*n) SC:O(m*n)
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int row[9][9] = {0}; int col[9][9] ={0}; int grid[9][9] ={0};

        for(int i = 0; i<9; i++){
            for(int j = 0; j<9; j++){
                if(board[i][j] != '.'){
                    int num = board[i][j]-'1';
                    int k = i/3*3+j/3;
                    if(row[i][num] || col[j][num] || grid[k][num]) return false;
                    row[i][num] = col[j][num] = grid[k][num] = 1;
                }
            }
        }

        return true;
    }
};

/*
此題只問說這個數獨板是否合法 而不在乎有沒有辦法解出來

*/
