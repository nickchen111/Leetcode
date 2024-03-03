/*
3071. Minimum Operations to Write the Letter Y on a Grid
*/


// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        int n = grid.size();
        int count1 = 0, count2 = 0, count0 = 0;
        int counta = 0, countb = 0, countc = 0;
        int center = n/2;
        for(int i = 0, j = 0; i < center && j < center; i++, j++){
            if(grid[i][j] == 0) count0 += 1;
            else if(grid[i][j] == 1) count1 += 1;
            else count2 += 1;
        }
        
        for(int i = 0, j = n-1; i < center && j > center; i++, j--){
            if(grid[i][j] == 0) count0 += 1;
            else if(grid[i][j] == 1) count1 += 1;
            else count2 += 1;
        }
        for(int i = center, j = center; i < n; i++){
            if(grid[i][j] == 0) count0 += 1;
            else if(grid[i][j] == 1) count1 += 1;
            else count2 += 1;
        }
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 0) counta += 1;
                else if(grid[i][j] == 1) countb += 1;
                else countc += 1;
            }
        }
        counta -= count0;
        countb -= count1;
        countc -= count2;
        
        int res = INT_MAX/2;
       
        res = min(count1 + count2 + counta + countb, min(res, count1 + count2 + counta + countc));
        res = min(res, min(count0 + count2 + countb + counta, count0 + count2 + countb + countc));
        res = min(res, min(count0 + count1 + countc + counta, count0 + count1 + countc + countb));
        
        return res;
        
    }
};

/*
以Y的東東為核心 去看他有幾個 0 1 2 分別對應要換幾次的0 or 1 or 2 然後另外其他的如果有包含到0 or 1 or 2的就要換掉 並且其他的要換到數字都一樣的狀況
*/
