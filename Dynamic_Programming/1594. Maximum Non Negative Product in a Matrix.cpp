/*
1594. Maximum Non Negative Product in a Matrix
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
    using LL = long long;
    int M = 1e9+7;
    LL dp_max[16][16];
    LL dp_min[16][16];
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        dp_min[0][0] = grid[0][0];
        dp_max[0][0] = grid[0][0];
        for(int i = 1; i < m; i++){
            dp_max[i][0] = grid[i][0]*dp_max[i-1][0];
            dp_min[i][0] = grid[i][0]*dp_max[i-1][0];
        }
        for(int j = 1; j < n; j++){
            dp_max[0][j] = grid[0][j]*dp_max[0][j-1];
            dp_min[0][j] = grid[0][j]*dp_max[0][j-1];
        }
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                dp_max[i][j] = max(dp_max[i-1][j] * grid[i][j], dp_max[i][j-1] * grid[i][j]);
                dp_max[i][j] = max(dp_max[i][j], max(dp_min[i-1][j] * grid[i][j], dp_min[i][j-1] * grid[i][j]));
                dp_min[i][j] = min(dp_min[i-1][j] * grid[i][j], dp_min[i][j-1] * grid[i][j]);
                dp_min[i][j] = min(dp_min[i][j], min(dp_max[i-1][j] * grid[i][j], dp_max[i][j-1] * grid[i][j]));
            }
        }
        
        return dp_max[m-1][n-1]%M < 0 ? -1 : dp_max[m-1][n-1]%M;
    }
};

/*
走迷宮DP 想求最大的乘積從左上走到右下
中間會經過正數or負數 只能往右or往下走 所以每一點的最大值都是從左or上來的 但是因為有負數所以這一題還要考慮最小的狀況

*/
