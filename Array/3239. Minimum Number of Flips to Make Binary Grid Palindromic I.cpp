/*
3239. Minimum Number of Flips to Make Binary Grid Palindromic I
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count1 = 0;
        int count2 = 0;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n/2; j++){
                int p1 = grid[i][j], p2 = grid[i][n-1-j];
                if(p1 != p2) {
                    count1 += 1;
                }
            }
        }
    
        for(int j = 0; j < n; j++){
            for(int i = 0; i < m/2; i++){
                int p1 = grid[i][j], p2 = grid[m-1-i][j];
                if(p1 != p2) {
                    count2 += 1;
                }
            }
        }
        
        return min(count1, count2);
        
    }
};
