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