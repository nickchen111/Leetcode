/*
2965. Find Missing and Repeated Values
*/

// TC:O(m*n) SC:O(n)
class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int missing = -1;
        int duplicate = -1;
        unordered_set<int> set;//紀錄出現的數字
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(set.find(grid[i][j]) == set.end())
                    set.insert(grid[i][j]);
                else duplicate = grid[i][j];
            }
        }
        
        for(int i = 1; i <= n*n; i++){
            if(set.find(i) == set.end()){
                missing = i;
                break;
            }
        }
        
        vector<int> res = {duplicate, missing};
        
        return res;
    }
};


/*
此題是之前找 missing repeat 變成二維數組的題目
repeat and missing
用一個set紀錄找到的數字 如果重複了 那當下數字就是重複的 在遍歷一次n*n的數組 找哪個數字沒出現過
*/
