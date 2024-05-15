/*
3030. Find the Grid of Region Average
*/

// TC:O(m*n*9) SC:O(2*m*n)
class Solution {
public:
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        int m = image.size(), n = image[0].size();
        int reg[501][501][2] = {};
        // m*n*9
        for(int i = 0; i < m-2; i++){
            for(int j = 0; j < n-2; j++){
                int sum = 0;
                bool is_region = true;
                for(int k = i; k < i+3; k++){
                    for(int l = j; l < j+3; l++){
                        sum += image[k][l];
                        if(k-1 >= i && abs(image[k][l] - image[k-1][l]) > threshold) is_region = false;
                        if(k+1 < i+3 && abs(image[k][l] - image[k+1][l]) > threshold) is_region = false;
                        if(l-1 >= j && abs(image[k][l] - image[k][l-1]) > threshold) is_region = false;
                        if(l+1 < j+3 && abs(image[k][l] - image[k][l+1]) > threshold) is_region = false;
                    }
                }
                if(is_region){
                    for(int k = i; k < i+3; k++){
                        for(int l = j; l < j+3; l++){
                            reg[k][l][0] += sum/9;
                            reg[k][l][1] += 1;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(reg[i][j][1]){
                    image[i][j] = reg[i][j][0] / reg[i][j][1];
                }
            }
        }

        return image;

    }
};

/*
不斷取網格內3x3的區域 區域內每個元素要跟他的上下左右數值絕對值小於等於 門檻值
問說每個元素應填入什麼數值
要比較上下左右 如果不合法那這整塊可以都不算
|a - c| + |b - d| == 1. -> b-d = 1 or -1 or 0 上or下or同個位置 -> 可以搭配左右一位 or 同個位置
那好像就是上下左右
然後相鄰的要比較的對象只有當下3*3格子內的元素就好 不用比到超過！

*/
