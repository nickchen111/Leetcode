/*
188. Best Time to Buy and Sell Stock IV
*/

//解法一： 此题是对之前股票系列I，II，III的综合考察，并推广到任意k次交易的条件。TC:O(n*k) SC:O(k) 
//一樣是去思考dp[i] 以這天為結尾可以獲得的最大利益為多少,下列程式將天數省略優化空間 只考慮在此天數下可以操作的買賣次數情況下會有的最大利益
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();//天數
        //hold 買的話算一次操作 sold是這天賣掉的狀態或是手上並沒有持股的意思
        // 原本的dp數組為 vector<vector<int>> sold(n, vector<int(k+1, INT_MIN/2));
        vector<int> sold(k+1, INT_MIN/2);
        vector<int> hold(k+1, INT_MIN/2);

        sold[0] = 0;
        hold[0] = 0;

        for(int i = 0; i < n; i++){
            auto sold_old = sold;
            auto hold_old = hold;
            for(int K = 1; K<=k; K++){
                sold[K] = max(hold_old[K]+prices[i], sold_old[K]);
                hold[K] = max(sold_old[K-1]-prices[i],hold_old[K]);
            }
        }

        int res = INT_MIN;
        for(int i = 0; i<=k; i++){
            res = max(res, sold[i]);
        }

        return res;

    }
};

//解法2 from HG : TC:O(n*lgp) SC:O(k) 
class Solution {
    int n;
public:
    int maxProfit(int k, vector<int>& prices) {
        n = prices.size();
        prices.insert(prices.begin(), 0);

        //探索f(x) = g(x)_max - a*x; 當 某個a 使得 x == k 就會停下來 or k在下凹曲線的右側最後就會找到peak點
        //如果找到的 次數 大於 最大利益的點xm 代表沒有限制 單純求最大利益就好 122題 f(xm) = g(x) - 0*xm
        //如果小於xm就是 f(k) 那就是714題的有手續費的狀況 峰值會越來越往左移 總有一天會跟k在同個x軸上 這時在把a*k加回去就是此題答案
        int left = 0; int right = *max_element(prices.begin(), prices.end()); //可以被扣的交易手續費最小到最大值
        while(left < right){
            int fee = left + (right - left)/2;// 0 1取 0 
            if(maxProfitwithFee(prices, fee)[1] > k){//說明交易費太小了 要提高一點來讓交易次數下降才能有最高的收益
                left = fee+1;
            }
            else right = fee;
        }

        return maxProfitwithFee(prices, left)[0]+left*k;// left 為交易手續費 k為進行了幾次交易
    }
    vector<int> maxProfitwithFee(vector<int>& prices, int fee){
        vector<int> sold(n+1, 0);
        vector<int> hold(n+1, 0);

        sold[0] = 0;
        hold[0] = INT_MIN/2;//虛擬的交易日 市場還沒開市
        int count_sold = 0;
        int count_hold = 0;


        for(int i = 1; i<=n; i++){
            if(sold[i-1] >= hold[i-1]+prices[i]){
                sold[i] = sold[i-1];
            }
            else{
                sold[i] = hold[i-1]+prices[i];
                count_sold = count_hold;
            }

            if(hold[i-1] >= sold[i-1]-prices[i]-fee){
                hold[i] = hold[i-1];
            }
            else{
                hold[i] = sold[i-1]-prices[i]-fee;
                count_hold = count_sold+1;
            }
        }

        return {sold[n], count_sold}; // 獲得資產以及count_sold次數
    }
};
/*
这里介绍一个惊为天人的解法，时间复杂度是O(NlogP)，其中P是prices的最大值。
我们令f(x)表示固定交易x次能收获的最大值。那么这个f(x)会长什么样子？它是一个上凸的函数。因为交易次数太少，赚的机会就少；交易次数太多，有些交易反而会亏钱。
所以在某个位置xm的地方，交易这个次数可以使得利益最大化。如果k>=xm，那么我们必然选择交易xm次。如果k<xm，那么我们必然选择交易k次。
对于前者，本质上就是没有约束，那么问题就转化为了122. Best Time to Buy and Sell Stock II. 所以这题的关键其实就是求后者的f(k).
虽然知道了f(x)的形状，但直接求解f(x)我们其实没有什么特别好的办法。接下用来有个神奇的技巧。
我们在令g(x)=f(x)-a*x，从形式上看，就是一个带有transaction fee的股票买卖问题，其中每买一次股票需要额外付出a。特别地，当a=0的时候，g(x)就是f(x)。
我们此时考虑，当a=1的时候相比于a=0的时候，g(x)的函数图像有什么变化呢？首先对任何的交易次数x而言，交易费的引入都会让利润受损，所以g(x)整体会向下移动。
另外，交易费的引入会让有些交易变得无利可图甚至亏损，最大利润所对应的股票交易次数一定会减少，所以g(x)的峰值会左移。
可以想见，随着a的增大，g(x)的峰值会向下向左移动。注意，x的定义域是离散的，所以峰值也一定对应着某个整数的x。
如果我们能找到某个a，使得g(x)的峰值恰好对应着x=k的时候，意味着f(k)-ak = g(x)_max. 如果g(x)_max和a都知道了，那么本题就得解。那么如何知道这样的a呢？
事实上，我们已经知道，随着a的增大，g(x)的峰值位置是向左单调移动的。我们可以用二分法搜索出这个a来，满足峰值是的位置是k。此时交易费a确定了，
那么问题就同714 Best Time to Buy and Sell Stock with Transaction Fee，可以知道最大利润，也就是g(x)的峰值。
这个二分的过程中，a的最小值是0，最大值就是max{prices}。如果k>xm，那么我们二分搜索是不会搜到峰值位置是k的，但是会最终将a的选择收敛到0，这也就达到我们的目的了。
*/



