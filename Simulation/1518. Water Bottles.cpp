/*
1518. Water Bottles
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int res = 0;
        while(numBottles >= numExchange){
            int divide = numBottles / numExchange;
            res += divide * numExchange;
            numBottles = (numBottles % numExchange) + divide;
        }

        res += numBottles;

        return res;
    }
};
