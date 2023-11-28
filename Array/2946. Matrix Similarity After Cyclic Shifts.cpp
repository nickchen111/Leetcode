/*
2946. Matrix Similarity After Cyclic Shifts
*/

// TC:O(m*n*k) SC:O(1)
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        vector<vector<int>> arr = mat;
        int m = arr.size(); int n = arr[0].size();
        for(int i = 0; i<m; i++){
            if(i%2 == 0){
                for(int t = 0; t < k; t++){
                    for(int j = 0; j<n-1; j++){
                    if(j == 0) swap(arr[i][j],arr[i][n-1]);
                    else swap(arr[i][j],arr[i][j-1]);
                    }
                }
            }
            else {
                for(int t = 0; t<k; t++){
                    for(int j = n-1; j>=1; j--){
                    if(j == n-1) swap(arr[i][j],arr[i][0]);
                    else swap(arr[i][j],arr[i][j+1]);
                    }
                }
              
            }
        }
        
        return arr == mat;
    }
};

