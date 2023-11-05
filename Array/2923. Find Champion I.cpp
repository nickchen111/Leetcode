/*
2923. Find Champion I
*/

//TC:O(n*n) SC:O(1) 
class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        //去找一個組合是除了自己本身以外皆是一的
        int res = 0;
        int m = grid.size(); int n = grid[0].size();
        for(int i = 0; i<m; i++){
            int count = 0;
            for(int j = 0; j<n; j++){
                if(grid[i][j] == 1) count+=1;
                if(count == m-1) res = i;
            }
        }
        
        return res;
    }
};
