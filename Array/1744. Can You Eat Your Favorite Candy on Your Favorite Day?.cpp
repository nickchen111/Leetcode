/*
1744. Can You Eat Your Favorite Candy on Your Favorite Day?
*/

// TC:O(n + m) SC:O(n + m)
class Solution {
    using LL = long long;
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int n = candiesCount.size();
        vector<LL> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + candiesCount[i-1];
        }

        vector<bool> res(queries.size());
        for(int i = 0; i < queries.size(); i++){
            LL type = queries[i][0], days = queries[i][1], cap = queries[i][2];
            LL lower = 1LL*(days);
            LL upper = cap*(days+1);
            LL cur = presum[type+1];
            LL cur2 = presum[type];
            if(lower >= cur || upper <= cur2){
                res[i] = false;
            }
            else res[i] = true;
        }

        return res;
    }
};

/*
這題給你一堆query 問說能否在某一天吃到某個類型的糖果 並且有規定每天吃糖果的上限
且要吃type i之前一定要吃完 i-1 包含以前的糖果
遇到這題會想說 用一個presum將所有在那天以前的糖果都先算出來 並且看我的參數吃糖果上限
乘上目前天數 是否可以超過以前的糖果數量 並且還要確認每天都要吃一顆的狀況下不會把當前想吃的糖果吃完
-> 1*totaldays-1 >= 當前所有糖果數 or 當前最大吃的量 <=當天以前所有糖果數 就無法達成
跟區間概念一樣 這兩個都不滿足時 就是true
*/
