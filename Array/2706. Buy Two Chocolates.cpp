/*
2706. Buy Two Chocolates
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int buyChoco(vector<int>& prices, int money) {
        int n = prices.size();
        int second = -1;
        int first = -1;
        if(prices[0] >= prices[1]) {
            first = prices[1];
            second = prices[0];
        }
        else{
            first = prices[0];
            second = prices[1];
        }
    
        for(int i = 2; i < n; i++){
            if(prices[i] <= first){
                second = first;
                first = prices[i];
            }
            else if(prices[i] < second){
                second = prices[i];
            }
        }

        int res = money;
        res = res - first - second;
        if(res < 0) return money;
        else return res;

    }
};


/*
找到數組中的兩個相加比money小的數字
sort or O(n)遍歷紀錄最小值
*/
