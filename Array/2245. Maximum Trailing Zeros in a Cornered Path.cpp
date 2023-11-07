/*
2245. Maximum Trailing Zeros in a Cornered Path
*/


// TC:O(5*m*n) SC:O(5*m*n)
class Solution {
public:
    int maxTrailingZeros(vector<vector<int>>& grid) {
        int m = grid.size(); int n = grid[0].size();
        vector<vector<int>> self2(m,vector<int>(n,0));
        auto self5 = self2;

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                int x = grid[i][j];
                while(x%2 == 0){
                    self2[i][j]+=1;
                    x/=2;
                }
                while(x%5 == 0){
                    self5[i][j]+=1;
                    x/=5;
                }
            }
        }

        vector<vector<int>> left2(m,vector<int>(n,0));
        vector<vector<int>> right2(m,vector<int>(n,0));
        vector<vector<int>> up2(m,vector<int>(n,0));
        vector<vector<int>> down2(m,vector<int>(n,0));
        vector<vector<int>> left5(m,vector<int>(n,0));
        vector<vector<int>> right5(m,vector<int>(n,0));
        vector<vector<int>> up5(m,vector<int>(n,0));
        vector<vector<int>> down5(m,vector<int>(n,0));

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                left2[i][j] = (j == 0 ? 0:left2[i][j-1])+self2[i][j];
                left5[i][j] = (j == 0 ? 0:left5[i][j-1])+self5[i][j];
            }
            for(int j = n-1;j>=0; j--){
                right2[i][j] = (j == n-1 ? 0:right2[i][j+1])+self2[i][j];
                right5[i][j] = (j == n-1 ? 0:right5[i][j+1])+self5[i][j];
            }
        }

        for(int j = 0; j<n; j++){
            for(int i = 0; i<m; i++){
                up2[i][j] = (i==0 ? 0:up2[i-1][j])+self2[i][j];
                up5[i][j] = (i==0 ? 0:up5[i-1][j])+self5[i][j];
            }
            for(int i = m-1; i>=0; i--){
                down2[i][j] = (i==m-1 ? 0:down2[i+1][j])+self2[i][j];
                down5[i][j] = (i==m-1 ? 0:down5[i+1][j])+self5[i][j];
            }
        }

        int res = 0;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                res = max(res, min((left2[i][j]+up2[i][j]-self2[i][j]),(left5[i][j]+up5[i][j]-self5[i][j])));
                res = max(res, min((left2[i][j]+down2[i][j]-self2[i][j]),(left5[i][j]+down5[i][j]-self5[i][j])));
                res = max(res, min((right2[i][j]+up2[i][j]-self2[i][j]),(right5[i][j]+up5[i][j]-self5[i][j])));
                res = max(res, min((right2[i][j]+down2[i][j]-self2[i][j]),(right5[i][j]+down5[i][j]-self5[i][j])));     
            }
        }

        return res;
    }
};
