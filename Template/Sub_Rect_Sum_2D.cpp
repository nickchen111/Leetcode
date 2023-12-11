/*
Sub_Rect_Sum_2D
*/

class RegionSum{
    vector<vector<int>> presum;
public:
    RegionSum(vector<vector<int>>& A){
        int m = A.size(), n = A[0].size();
        presum.resize(m+1);
        for(int i = 0; i<=m; i++){
            presum[i].resize(n+1);
        }

        for(int i = 1; i<=m; i++){
            for(int j = 1; j<=n; j++){
                int a = presum[i-1][j];
                int b = presum[i][j-1];
                int c = presum[i-1][j-1];
                presum[i][j] = a+b-c+A[i-1][j-1];
            }
        }
    }

    int query(int i, int j, int x, int y){
        return presum[x+1][y+1]-presum[x+1][j]-presum[i][y+1]+presum[i][j];
    }

};
