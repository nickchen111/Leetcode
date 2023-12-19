/*
661. Image Smoother
*/


// TC:O(m*n*8) SC:O(1)
class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size();
        int n = img[0].size();
        vector<vector<int>> res(m, vector<int>(n));

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int sum = img[i][j];
                int count = 1;
                if(i + 1 < m && j + 1 < n){
                    sum += img[i+1][j+1];
                    count += 1;
                }
                if(i + 1 < m){
                    sum += img[i+1][j];
                    count += 1;
                }
                if(i - 1 >= 0){
                    sum += img[i-1][j];
                    count += 1;
                }
                if(j + 1 < n){
                    sum += img[i][j+1];
                    count += 1;
                }
                if(j - 1 >= 0){
                    sum += img[i][j-1];
                    count += 1;
                }
                if(i - 1 >= 0 && j - 1 >= 0){
                    sum += img[i-1][j-1];
                    count += 1;
                }
                
                if(i + 1 < m && j - 1 >= 0){
                    sum += img[i+1][j-1];
                    count += 1;
                }
                if(i - 1 >= 0 && j + 1 < n){
                    sum += img[i-1][j+1];
                    count += 1;
                }

                res[i][j] = sum/count;
            }
        }

        return res;
    }
};
