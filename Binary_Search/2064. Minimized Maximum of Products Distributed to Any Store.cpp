/*
2064. Minimized Maximum of Products Distributed to Any Store
*/


// TC:O(mlgk) SC:O(1)
class Solution {
    int m, n;
public:
    int minimizedMaximum(int n, vector<int>& quantities) {
        this->n = n;
        m = quantities.size();
        int left = 1, right = 1e5;
        while(left < right){
            int mid = left + (right - left)/2;
            if(check(mid,quantities)){
                right = mid;
            }
            else left = mid + 1;
        }

        return left;
    }
    bool check(int cap, vector<int>& quantities){
        int res = 0;
        for(int i = 0; i < m; i++){
            if(quantities[i] % cap == 0){
                res += quantities[i] / cap;
            } 
            else res += quantities[i] / cap + 1;
        }

        return res <= n;
    }
};

/*
n間店家 有m種商品 每種商品有他的個數 必須分配商品給n個店家follow一些條件
每個店家只能給一種商品最多 但是可任意給數量
請找出分配數量中最大值 此最大值需最小化
簡化版: 如果先考量沒有商品種類狀況 那就是平均分後的最大值

現在多了商品種類 題目已經說店家數量 >= 商品種類 所以考慮兩種狀況
商品種類等於店家數量 -> 答案就是商品裡最多那項
thought1: M < N -> 最多那項希望盡量拆分 拆分標準為何？ 拆分一半? 並且看當前商品種類多寡 不斷將最多種類的做拆分
ex : 10 7 5 3 , n = 9 -> 7/ 7 7 5 3 3  -> 7  很難說最佳策略到底要怎麼分才好 端看商店數量
thought2 : 因為很難界定怎麼分最好 感覺可以用binary search猜一個數字 看看能不能用這個數字裝
ex : 每一家商店最多裝五個 開始裝每個商品 對每個商品數量做除法 除不盡自動加一 看最後數量是否沒有超過m
*/
