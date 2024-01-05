/*
1072. Flip Columns For Maximum Number of Equal Rows
*/

// TC:O(m*n) SC:O(m*N)
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        unordered_map<string, int> map;
        for(int i = 0; i < m; i++){
            string str, reverse_str;
            for(int j = 0; j < n; j++){
                if(matrix[i][j] == 1){
                    str.push_back('1');
                    reverse_str.push_back('0');
                }
                else {
                    str.push_back('0');
                    reverse_str.push_back('1');
                }
            }

            map[str] += 1;
            map[reverse_str] += 1;
        }

        int res= 0;
        for(auto &p : map){
            res = max(res, p.second);
        }

        return res;
    }
};

// 問說每次能翻轉某一column上所有元素 可以翻任意次數 如果讓某一row上所有數字都一樣（只會有0 1）最多可以讓幾個row出現一樣數字
