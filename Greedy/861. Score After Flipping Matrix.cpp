/*
861. Score After Flipping Matrix
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    int matrixScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < m; i++){
            if(grid[i][0] == 0){
                for(int j = 0; j < n; j++){
                    grid[i][j] = 1 - grid[i][j];
                }
            }
        }

        int res = (1<<(n-1))*m;
        
        for(int j = 1; j < n; j++){
            int count0 = 0;
            int count1 = 0;
            for(int i = 0; i < m; i++){
                if(grid[i][j] == 1) count1 += 1;
                else count0 += 1;
            }
            
            res += (1<<(n-j-1))*max(count0,count1);
        }

        return res;
    }
};

/*
問說每一個row 換成十進位的總和最大可以是多少
每一個row or col 都可以翻轉數字
首先肯定先針對所有row 讓他們的第一個字都可以是1
再來就是針對第二行 看翻轉後是否1會變多 or not 每行都這樣檢查 就可以獲得最終答案
*/
