/*
2536. Increment Submatrices by One
*/

// TC:O(n*n + k) SC:O(n*n)
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n+1, vector<int>(n+1,0));
        for(auto query : queries){
            int row1 = query[0], col1 = query[1], row2 = query[2], col2 = query[3];
            diff[row1][col1] += 1;
            diff[row1][col2+1] -= 1;
            diff[row2+1][col1] -= 1;
            diff[row2+1][col2+1] += 1;
        }

        vector<vector<int>> res(n, vector<int>(n,0));
        res[0][0] = diff[0][0];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int a = (i == 0 ? 0: res[i-1][j]);
                int b = (j == 0 ? 0: res[i][j-1]);
                int c = ((i == 0 || j == 0 ) ? 0: res[i-1][j-1]);
                res[i][j] = a + b - c + diff[i][j];
            }
        }

        return res;
    }
};
