/*
3100. Water Bottles II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int sum = 0;
        int empty = 0;
        while(true){
            sum += numBottles;
            empty += numBottles;
            numBottles = 0;
            int diff = empty - numExchange;
            if(diff >= 0 && empty != 0) {
                numBottles += 1;
                empty -= numExchange;
                numExchange+=1;
            }
            else break;
        }
        
        return sum;
    }
};

/*
每次可以喝完水 or 用 numexchange空瓶換一個新的水 numexchange+1
模擬過程 numBottles != 0 -> sum += numB; Ex -= Empty , diff += numBot
numBot -= sum ... 
*/
