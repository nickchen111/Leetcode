/*
3000. Maximum Area of Longest Diagonal Rectangle
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int m = dimensions.size();
        int n = dimensions[0].size();
        int res = -1;
        double maxVal = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                double sum = sqrt(dimensions[i][0]*dimensions[i][0] + dimensions[i][1]*dimensions[i][1]);
                if(sum > maxVal){
                    maxVal = sum;
                    res = dimensions[i][0]*dimensions[i][1];
                }
                else if(sum == maxVal){
                    res = max(res, dimensions[i][0]*dimensions[i][1]);
                }
            }
        }
        
        return res;
    }
};

/*
要求每個矩形他的對角線最大那項他的面積多少 如果對角線長度相同 取最大面積的
*/
