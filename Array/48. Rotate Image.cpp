/*
48. Rotate Image
*/

//TC:O(n*n) SC:O(1)
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        //先將矩陣鏡像翻轉
        for(int i = 0; i<n; i++){
            //此寫法為採用右邊的三角形 
            //也可以寫成左邊三角形 for(int j = 0; j<i; j++)
            for(int j = i; j<n; j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }

        //再將他們的每一行的字左右互換
        for(int i = 0; i < n; i++){
            int left = 0; int right = n-1;
            while(left < right){
                swap(matrix[i][left],matrix[i][right]);
                left++;
                right--;
            }
        }
    }
};
