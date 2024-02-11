/*
3033. Modify the Matrix
*/

// TC:O(m*n) SC:O(n + k) k 為有-1的格子數量
class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int maxVal = INT_MIN;
        auto res = matrix;
        vector<pair<int,int>> memo;
        vector<int> maxV(n);
        
        for(int j = 0; j < n; j++){
            int maxVal = INT_MIN;
            for(int i = 0; i < m; i++){
                if(maxVal < matrix[i][j]){
                    maxVal = matrix[i][j];
                }
                if(matrix[i][j] == -1){
                    memo.push_back({i,j});
                }
            }
            maxV[j] = maxVal;
        }
        
        for(auto p : memo){
            res[p.first][p.second] = maxV[p.second];
        }
        
        return res;
    }
};
