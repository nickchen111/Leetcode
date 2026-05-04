 class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        //先transpose 在左右對調
        int m = matrix.size(); int n = matrix[0].size();

        for(int i = 0; i<m; i++){
            //左邊三角形
            for(int j = i; j>=0; j--){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        //左右對調
        for(int i = 0; i<m;i++){
            int left = 0; int right = n-1;
            while(left < right){
                swap(matrix[i][left],matrix[i][right]);
                left++; right--;
            }
        }
    }
};