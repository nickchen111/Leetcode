/*
1380. Lucky Numbers in a Matrix
*/

// TC:O(m*n) SC:O(m+n)
class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> row(m, INT_MAX);
        vector<int> col(n, INT_MIN);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(row[i] > matrix[i][j]){
                    row[i] = matrix[i][j];
                }
                if(col[j] < matrix[i][j]){
                    col[j] = matrix[i][j];
                }
            }
        }

        vector<int> res;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(row[i] == col[j]){
                    res.push_back(matrix[i][j]);
                }
            }
        }

        return res;
    }
};
