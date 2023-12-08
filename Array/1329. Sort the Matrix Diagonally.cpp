/*
1329. Sort the Matrix Diagonally
*/

// TC:O(mlgn + nlgm) SC:O(m + n)
class Solution {
    int m, n;
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        //可以注意到只有第一排第一列會是起點
        m = mat.size(); n = mat[0].size();

        for(int i = 0; i < m; i++){
            solve(mat, i, 0);
        }
        for(int j = 0; j < n; j++){
            solve(mat, 0, j);
        }

        return mat;
    }

    void solve(vector<vector<int>>& mat, int x, int y){
        vector<int> arr;
        for(int i = x , j = y; i < m && j < n; i++, j++){
            arr.push_back(mat[i][j]);
        }
        sort(arr.begin(), arr.end());
        int idx = 0;
        for(int i = x , j = y; i < m && j < n; i++, j++){
            mat[i][j] = arr[idx];
            idx++;
        }
    }
};

/*
x x x x x x x x x
x x x x x x x x x 
x x x x x x x x x 
x x x x x x x x x 
x x x x x x x x x
*/
