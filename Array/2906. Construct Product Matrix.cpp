/*
/*2906. Construct Product Matrix
*/

// Two pass 空間優化 把後綴存到答案中 TC:O(m*n) SC:O(1)
class Solution {
    int M = 12345;
    using LL = long long;
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> res(m, vector<int>(n,1));

        for(int i = m-1; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                if(j+1 < n) {
                    res[i][j] = ((LL)(res[i][j+1])%M * (LL)grid[i][j+1]%M) % M;
                } 
                else {
                    if(i+1 < m){
                        res[i][j] = ((LL)(res[i+1][0])%M * (LL)grid[i+1][0]%M) % M;
                    }
                    else {
                        res[i][j] = 1;
                    }
                }
            }
        }
        
        LL prefix = 1;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                res[i][j] = ((LL)res[i][j] % M * prefix % M) % M;
                prefix = (prefix * (LL)grid[i][j] % M) % M;
            }
        }

        return res;
    }
};

// Two pass TC:O(m*n) SC:O(m*n)
class Solution {
    int M = 12345;
    using LL = long long;
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<LL> sufsum(m*n+1,1);
        
        for(int i = m-1; i >= 0; i--){
            for(int j = n-1; j >= 0; j--){
                if(i*n+j-1 >= 0)
                    sufsum[i*n+j-1] = (sufsum[i*n+j]%M * (LL)grid[i][j]%M) % M;
            }
        }
        vector<vector<int>> res(m, vector<int>(n));
        LL prefix = 1;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                res[i][j] = (prefix * sufsum[i*n+j]) % M;
                prefix = (prefix * (LL)(grid[i][j]%M)) % M;
            }
        }

        return res;
    }
};

// Three pass TC:O(m*n) SC:O(m*n)
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
