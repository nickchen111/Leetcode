// TC:O(1) SC:O(1)
class Solution {
public:
    int findClosest(int x, int y, int z) {
        if (abs(x - z) < abs(y - z)) return 1;
        else if (abs(x - z) == abs(y - z)) return 0;
        else return 2;
    }
};
