/*
2132. Stamping the Grid
*/

// TC:O(m*n) SC:O(m*n)
//304題
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
class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(); int n = grid[0].size();
        //grid裡面有多少個x O(1)時間可以知道
        RegionSum Grid(grid);
        //判斷哪些地方是可以放stamp的
        vector<vector<int>> stamp(m,vector<int>(n));
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                int x = i+stampHeight-1;
                int y = j+stampWidth-1;
                if(x >=m || y>=n) continue;
                int area = Grid.query(i,j,x,y);
                if(area == 0) stamp[x][y] =1;
            }
        }

        //知道哪些地方可以放stamp在O(1)時間確認
        RegionSum Stamp(stamp);
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1) continue;
                int x = min(m-1,i+stampHeight-1);
                int y = min(n-1,j+stampWidth-1);
                int area = Stamp.query(i,j,x,y);
                //如果合法需被涵蓋的點不包含任何的可以被涵蓋的紀錄點
                if(area ==0) return false;
            }
        }

        return true;
    }
};

/*
此題算是2D presum挺特別的題目 要用到兩次二維presum概念 第一次先將可以放入郵票的點在此方匡右下角標記
第二次在每個應該可放入的點判斷是否會有標記可以的點 如果沒有代表規定的郵票大小不足以涵蓋所有合法區間
*/
