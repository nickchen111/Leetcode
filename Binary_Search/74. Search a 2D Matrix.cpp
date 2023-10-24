/*
74. Search a 2D Matrix
*/


//二分  TC:O(lgm*n) SC:O(1)
class Solution {
    int m,n;
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        m = matrix.size(); n = matrix[0].size();
        int left = 0;
        int right = m*n-1;
        while(left < right){
            int mid = left + (right - left)/2;
            int x = mid/n;
            int y = mid%n;
            if(matrix[x][y] > target){
                right = mid-1;
            }
            else if(matrix[x][y] < target){
                left = mid+1;
            }
            else{
                return true;
            }
        }
        int x = left/n;
        int y = left%n;
        if(matrix[x][y] == target) return true;
        else return false;
    } 
};
