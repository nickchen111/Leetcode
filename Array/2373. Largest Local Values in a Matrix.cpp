/*
2373. Largest Local Values in a Matrix
*/

// TC:O(m*n*9) SC:O(m*n)
class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> res(m-2, vector<int>(n-2));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int maxVal = grid[i][j];
                if(i + 2 < m && j + 2 < n){
                    for(int k = i; k < i+3; k++){
                        for(int t = j; t < j+3; t++){
                            maxVal = max(maxVal, grid[k][t]);
                        }
                    }

                    res[i][j] = maxVal;
                }
            }
        }

        return res;
    }
};

/*
把所有3*3最大的數字找出 然後組成n-2*n-2個的數組
m*n*3*3
*/
