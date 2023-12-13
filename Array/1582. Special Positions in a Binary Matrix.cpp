/*
1582. Special Positions in a Binary Matrix
*/

// TC:O(m*n) SC:O(m+n)
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int m = mat.size(); int n = mat[0].size();
        vector<int> row(m);
        vector<int> col(n);

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j] == 1){
                    row[i] += 1;
                    col[j] += 1;
                }
            }
        }

        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j] == 1){
                    if(row[i] == 1 && col[j] == 1) res +=1;
                }
            }
        }
        return res;
    }
};
