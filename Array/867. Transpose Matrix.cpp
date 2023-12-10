/*
867. Transpose Matrix
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int m = matrix.size(); 
        int n = matrix[0].size();
        vector<vector<int>> res(n, vector<int>(m));//此題無法原地轉換 畢竟mn不同
        for(int i = 0; i < m; i ++){
            for(int j = 0; j < n; j++){
                res[j][i] = matrix[i][j]; 
            }
        }
        
        return res;
    }
};

/*
此題就是考用程式寫出轉置矩陣
[0 1] -> [1 0]換
*/
