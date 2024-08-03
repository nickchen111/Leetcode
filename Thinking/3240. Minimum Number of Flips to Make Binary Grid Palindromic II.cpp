/*
3240. Minimum Number of Flips to Make Binary Grid Palindromic II
*/


// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = (int)grid.size(), n = (int)grid[0].size();
        int ans = 0;
        
        for (int i = 0; i < m / 2; i++){
            for (int j = 0; j < n / 2; j++){
                int co[2] = {0, 0};
                co[grid[i][j]]++;
                co[grid[i][n - 1 - j]]++;
                co[grid[m - 1 - i][j]]++;
                co[grid[m - 1 - i][n - 1 - j]]++;
                ans += min(co[0], co[1]);
            }
        }
        
        if (m % 2 && n % 2 && grid[m / 2][n / 2]) ans++;

        bool flag = false;
        int co1 = 0;
        
        if (m % 2){
            for (int i = 0; i < n / 2; i++){
                if (grid[m / 2][i] != grid[m / 2][n - 1 - i]){
                    ans++;
                    flag = true;
                }
                else if (grid[m / 2][i]) co1 += 2;
            }
        }
        if (n % 2){
            for (int i = 0; i < m / 2; i++){
                if (grid[i][n / 2] != grid[m - 1 - i][n / 2]){
                    ans++;
                    flag = true;
                }
                else if (grid[i][n / 2]) co1 += 2;
            }
        }

        if (!flag && co1 % 4) ans += 2;

        return ans;
    }
};
