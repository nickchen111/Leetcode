/*
2022. Convert 1D Array Into 2D Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        vector<vector<int>> res(m, vector<int>(n));
        int k = original.size();
        if(k != m*n) return {};

        for(int i = 0; i < k; i++){
            res[i/n][i%n] = original[i];
        }

        return res;
    }
};
