/*
1716. Calculate Money in Leetcode Bank
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int totalMoney(int n) {
        int sum = 0;

        if(n <= 7){
            for(int i = 1; i <= n; i++){
                sum+=i;
            }
            return sum;
        }
        else {
            int x = n/7; // 3
            for(int i = 1; i <= 7; i++){
                sum += i;
            }

            int r = n % 7;// 5
            int prev_sum = sum;
            for(int i = 1; i < x; i++){
                sum = sum + prev_sum + 7;
                prev_sum += 7;
            }
            for(int i = x+1; i < x+1+r; i++){
                sum += i;
            }

            return sum;
        }
    }
};

/*
%7 -> 1 2 3 4 5 6 7 
      2 3 4 5 6 7 8
      3 4 5 6 7 8 9
      4 5 6 7 8 
      ...
      
*/
