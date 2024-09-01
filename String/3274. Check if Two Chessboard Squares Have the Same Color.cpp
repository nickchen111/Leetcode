/*
3274. Check if Two Chessboard Squares Have the Same Color
*/

// TC:O(1) SC:O(1)
class Solution {
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2) {
        int num1 = ((coordinate1[0]-'a') % 2 == (coordinate1[1]-'0') % 2) ? 1 : 0;
        int num2 = ((coordinate2[0]-'a') % 2 == (coordinate2[1]-'0') % 2) ? 1 : 0;
        if(num1 == num2) return true;
        else return false;
    }
};
