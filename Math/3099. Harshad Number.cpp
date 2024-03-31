/*
3099. Harshad Number
*/

// TC:O(1) SC:O(1)
class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) {
        int sum = 0;
        int tmp  = x;
        while(tmp != 0){
            sum = sum + tmp%10;
            tmp /= 10;
        }
        if(x % sum == 0) return sum;
        else return -1;
    }
};

