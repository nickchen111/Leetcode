/*
1861. Rotating the Box
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size();
        int n = box[0].size();
        vector<vector<char>> res(n, vector<char>(m,'.'));
        for(int i = 0; i < m; i++) {
            int left = n-1, right = n-1;
            while(left >= 0) {
                if(box[i][left] == '*') {
                    res[left][m-1-i] = '*';
                    right = left - 1;
                }
                else if(box[i][left] == '#') {
                    res[right][m-1-i] = '#';
                    right--;
                }
                
                left--;
            }
        }

        return res;

    }
};
