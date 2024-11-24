/*
1975. Maximum Matrix Sum
*/

// TC:O(m*n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        LL sum = 0;
        int count_neg = 0;
        LL minVal = LLONG_MAX;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(matrix[i][j] < 0) {
                    count_neg += 1;
                }
                minVal = min(minVal, (LL)abs(matrix[i][j]));
                sum += abs(matrix[i][j]);
            }
        }
        if((count_neg % 2)) {
            sum -= minVal*2;
        }
        
        return sum;
    }
};
