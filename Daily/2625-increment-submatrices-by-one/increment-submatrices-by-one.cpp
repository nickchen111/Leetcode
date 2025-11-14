class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n+1, vector<int>(n+1));
        for(auto q : queries){
            int a = q[0], b =  q[1], c = q[2], d = q[3];
            diff[a][b] += 1;
            diff[a][d+1] -= 1;
            diff[c+1][b] -= 1;
            diff[c+1][d+1] += 1;
        }

        vector<vector<int>> res(n, vector<int>(n,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int a = (i == 0 ? 0 : res[i-1][j]);
                int b = (j == 0 ? 0 : res[i][j-1]);
                int c = (i == 0 || j == 0 ? 0 : res[i-1][j-1]);
                res[i][j] = a + b - c + diff[i][j];
            }
        }

        return res;
    }
};