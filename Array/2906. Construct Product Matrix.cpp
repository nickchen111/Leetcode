/*
/*2906. Construct Product Matrix
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        //紀錄他們的前面與後面
        int n = grid.size();
        int m = grid[0].size();
        int M = 12345;
        vector<int> pre(n*m+1,1);
        vector<int> post(n*m+1,1);
        
        for(int i = 0; i<n;i++){
            for(int j = 0; j<m; j++){
                pre[i*m+j+1] = ((pre[i*m+j]%M)*(grid[i][j]%M))%M;
            }
        }
        
        for(int i = n-1; i>=0;i--){
            for(int j = m-1; j>=0;j--){
                if(i*m+j-1>=0)
                    post[i*m+j-1] =((post[i*m+j]%M)*(grid[i][j]%M))%M;
            }
        }
        vector<vector<int>> res(n,vector<int>(m));
        for(int i = 0; i<n;i++){
            for(int j = 0; j<m; j++){
                res[i][j] = ((pre[i*m+j]%M)*(post[i*m+j]%M))%M;
            }
        }
        
        return res;
    }
};

/*
1 2 3 4 
5 6 7 8 
9 0 1 2 
*/
