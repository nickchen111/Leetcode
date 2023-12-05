/*
1688. Count of Matches in Tournament
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfMatches(int n) {
        int res = 0;
        while(n != 1){
            res += n/2;
            if(n % 2 == 1){
                n = n/2 + 1;
            }
            else n /= 2;
        }

        return res;
    }
};
