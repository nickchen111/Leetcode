/*
73. Set Matrix Zeroes
*/

//Best Method
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        //此題特色在於[0,0]這個位置不能先做 先處理第一行開始的行列 將它加入到最左或者最上排中
        bool row = false; bool col = false;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(matrix[i][j] == 0){
                    if(i == 0) row = true;
                    if(j == 0) col = true;
                    //將他們的左排上排置為0
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for(int i = 1; i<m; i++){
            if(matrix[i][0] == 0){
                for(int j = 1; j<n; j++){
                    matrix[i][j] = 0;
                }
            }
        }

        for(int j = 1; j<n; j++){
            if(matrix[0][j] == 0){
                for(int i = 1; i<m; i++){
                    matrix[i][j] = 0;
                }
            }
        }

        if(row){
            for(int j = 0; j<n; j++){
                matrix[0][j] = 0;
            }
        } 
        if(col){
            for(int i = 0; i<m; i++){
                matrix[i][0] = 0;
            }
        }
    }
};

// TC:O(((m*n)*(m+n))) SC:O(1)
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        //TC m*n(m+n) SC:O(1)解法
        int m = matrix.size(); int n = matrix[0].size();
        //set all must-to be zero element to -6666
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(matrix[i][j] == 0){
                    for(int k = 0; k<n;k++){
                        if(matrix[i][k] != 0) matrix[i][k] = -6666;
                    }
                }
            }
        } 

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(matrix[i][j] == 0){
                    for(int k = 0; k<m;k++){
                        if(matrix[k][j] != 0) matrix[k][j] = -6666;
                    }
                }
            }
        } 

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(matrix[i][j] == -6666) matrix[i][j] = 0;
            }
        }
    }
};

//TC:O(n*m) SC:O(m*n) by hash set
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        //TC m*n SC:O(m+n)解法
        int m = matrix.size(); int n = matrix[0].size();
        unordered_set<int> row;
        unordered_set<int> col;
        for(int i = 0; i<m; i++){
            for(int j=0; j<n; j++){
                if(matrix[i][j] == 0){
                    row.insert(i);
                    col.insert(j);
                }
            }
        }

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(row.count(i) > 0 || col.count(j) > 0){
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
