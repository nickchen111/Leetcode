/*
240. Search a 2D Matrix II
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //從左下或者右上開始都行
        int m = matrix.size(); int n = matrix[0].size();
        int left = m-1;
        int right = 0;
        while(left >=0 && right < n){
            if(matrix[left][right] == target) return true;
            else if(matrix[left][right] > target){
                left--;
            }
            else if(matrix[left][right] < target){
                right++;
            }
        }

        return false;
    }
};

/*
此題是用點小技巧來用二分的方法 在線性時間下得到結果
*/
