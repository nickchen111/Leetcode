/*
3127. Make a Square with the Same Color
*/

// TC:O(n^2) SC:O(n^2) n = 3
class Solution {
public:
    bool canMakeSquare(vector<vector<char>>& grid) {
        int n = grid.size();
        vector<vector<int>> presum(n+1, vector<int>(n+1));
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + (grid[i-1][j-1] == 'W'); // 之後如果結果是1 or 3
            }
        }
        
        for(int i = 2; i <= n; i++){
            for(int j = 2; j <= n; j++){
                int count = presum[i][j] - presum[i-2][j] - presum[i][j-2] + presum[i-2][j-2];
                if(count == 1 || count == 3 || count == 0 || count == 4) return true;
            }
        }
        
        return false;
    }
};

/*
3*3之中 可以換頂多一次顏色 
問說是否能讓某一個2*2中都是一樣顏色
*/
