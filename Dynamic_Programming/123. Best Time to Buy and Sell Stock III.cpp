/*
123. Best Time to Buy and Sell Stock III
*/

//將天數跟交易次數考慮進dp裡 設置兩個狀態 持有or 未持有 TC:O(n*k) SC:O(n)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);
        vector<vector<int>> sold(n+1, vector<int>(3, 0));
        vector<vector<int>> hold(n+1, vector<int>(3, INT_MIN/2));
        
        sold[0][0] = 0;
        hold[0][1] = INT_MIN/2;//虛擬日
        sold[1][0] = 0;//第一天不買 
        hold[1][1] = -prices[1];


        for(int i = 2; i<=n; i++){
            for(int j = 1; j<=2; j++){
                sold[i][j] = max(hold[i-1][j]+prices[i], sold[i-1][j]);// 邊界 hold[1][1] sold[1][2]
                hold[i][j] = max(hold[i-1][j], sold[i-1][j-1]-prices[i]);//邊界 hold[1][1] sold[1][0]
            }
        }

        int res = max(sold[n][1],sold[n][2]);

        return res < 0 ? 0:res;

    }
};

//優化  時間空間一起 TC:O(n) SC:O(1)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        prices.insert(prices.begin(), 0);
        int hold1 = INT_MIN/2, sold1 = 0, hold2 = INT_MIN/2, sold2 = 0;

        for(int i = 1; i<=n; i++){
            int hold1_tmp = hold1;
            int hold2_tmp = hold2;
            int sold1_tmp = sold1;
            int sold2_tmp = sold2;


            hold1 = max(hold1_tmp, 0-prices[i]);
            hold2 = max(hold2_tmp, sold1_tmp-prices[i]);
            sold1 = max(sold1_tmp, hold1_tmp+prices[i]);
            sold2 = max(sold2_tmp, hold2_tmp+prices[i]);
        }

        return max(sold1, sold2);

    }
};





/*
限制交易次數
一樣天數的限制來寫看看
這題考察點在於要想到hold 在天數較少的情況下 完成較高的操作次數是不可能的 必須初始化為INT_MIN/2 
而sold 是有可能的 初始化為 0 
*/
