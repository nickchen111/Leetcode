/*
304. Range Sum Query 2D - Immutable
*/


class NumMatrix {
private:
    // 定義：preSum[i][j] 记录 matrix 中子矩阵 [0, 0, i-1, j-1] 的元素和 想求區間 1跟4之間的總和是用 presum[5]-presum[1] 切記！
    vector<vector<int>> presum;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size(); //不用減一因為跟presum的遍歷範圍有關
        if(m == 0 || n == 0) return;
        // 构造前缀和矩阵
        presum = vector<vector<int>>(m+1, vector<int>(n+1));

        for(int i = 1; i<=m; i++){
            for(int j = 1; j<=n; j++){
                // 计算每个矩阵 [0, 0, i, j] 的元素和
                presum[i][j] = presum[i-1][j] + presum[i][j-1] + matrix[i-1][j-1] - presum[i-1][j-1];
            }
        }
    }
    // 计算子矩阵 [x1, y1, x2, y2] 的元素和
    int sumRegion(int row1, int col1, int row2, int col2) {
        // 目标矩阵之和由四个相邻矩阵运算获得
        return presum[row2+1][col2+1] - presum[row1][col2+1] - presum[row2+1][col1] + presum[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

 /*
 解題思維：
 這題的brute force就是每次遇到一個情況就用兩個for 迴圈來慢慢計算 
 比較好的辦法是利用前綴和的方式來解此題
1.需自己定義前綴和函式 利用圖像思考方式求出每個presum的值
2.最後利用圖形的加加減減求出指定範圍內的和

 前綴和(presum)	tc: o(m*n) sc:o((m+1) * (n+1))
 */
