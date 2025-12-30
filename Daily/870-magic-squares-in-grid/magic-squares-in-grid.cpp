class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i + 2 < m && j + 2 < n){
                    vector<int> count(10);
                    bool flag = 1;
                    int target = grid[i][j] + grid[i+1][j] + grid[i+2][j];
                    for(int k = i; k < i+3; k++){
                        int sum = 0;
                        for(int t = j; t < j + 3; t++){
                            if(grid[k][t] > 9 || grid[k][t] == 0){
                                flag = 0;
                                break;
                            }
                            sum += grid[k][t];
                            count[grid[k][t]] += 1;
                            if(count[grid[k][t]] >= 2){
                                flag = 0;
                                break;
                            }
                        }
                        if(sum != target) {
                            flag = 0;
                        }
                        if(flag == 0) break;
                    }

                    if(flag == 0) continue;
                    for(int k = j; k < j+3; k++){
                        int sum = 0;
                        for(int t = i; t < i + 3; t++){
                            sum += grid[t][k];
                        }
                        if(sum != target) {
                            flag = 0;
                        }

                        if(flag == 0) break;
                    }
                    if(flag == 0) continue;
                    int diasum1 = 0;
                    for(int k = i, t = j; k < i+3 && t < j + 3; k++, t++){
                        diasum1 += grid[k][t];
                    }
                    if(diasum1 != target) {
                        flag = 0;
                    }
                    if(flag == 0) continue;
                    int diasum2 = 0;
                    for(int k = i, t = j+2; k < i+3 && t >= j; k++, t--){
                        diasum2 += grid[k][t];
                    }

                    if(diasum2 != target) {
                        flag = 0;
                    }
                    if(flag == 0) continue;
                    res += 1;
                }
            }
        }


        return res;
    }
};

/*
1-9 不能重複 而且有可能有10-15 
3x3 矩陣中 符合 row col diag 總和為相同的矩陣有幾個
*/