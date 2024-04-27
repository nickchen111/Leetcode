/*
3128. Right Triangles
*/

// TC:O(m*n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long numberOfRightTriangles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        unordered_map<int,LL> col;
        
        long long count = 0;
        for(int i = 0; i < m; i++){
            LL row = 0;
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    if(col[j] > 0) {
                        count += row*col[j];
                        
                    }
                    col[j] += 1;
                    row += 1;
                } 
            }
        }
        
        col.clear();
        
        
        for(int i = m-1; i >= 0; i--){
            LL row = 0;
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                     if(col[j] > 0) {
                        count += row*col[j];
                        
                    }
                    col[j] += 1;
                    row += 1;
                } 
            }
        }
        
        col.clear();
       
        
        
        for(int i = 0; i < m; i++){
            LL row = 0;
            for(int j = n-1; j >= 0; j--){
                if(grid[i][j] == 1){
                     if(col[j] > 0) {
                        count += row*col[j];
                        
                    }
                    col[j] += 1;
                    row += 1;
                } 
            }
        }
        col.clear();
      
        
        for(int i = m-1; i >= 0; i--){
            LL row = 0;
            for(int j = n-1; j >= 0; j--){
                if(grid[i][j] == 1){
                     if(col[j] > 0) {
                        count += row*col[j];
                        
                    }
                    col[j] += 1;
                    row += 1;
                } 
            }
        }
        
        return count;
    }
};

/*
這題就是每個點都要看自己本身的上下左右是否有1 但是需要4 pass
有的話就將當下row走過有的數量*col[j]
*/
