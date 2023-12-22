/*
2952. Minimum Number of Coins to be Added
*/

// TC:O(nlgn) SC:O(1) 數學歸納法 
class Solution {
    unordered_set<int> set;
public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());
        int i = 0;
        int res = 0;
        int limit = 0;
        while(limit < target){
            //代表沒有相交
            if(i == coins.size() || limit+1 < coins[i]){
                res++;
                limit += limit+1;
            }
            else {
                limit += coins[i];
                i++;
            }
        }

        return res;
    }
};

/*
給你一個數字 再給你一組數組想用一數組內數字構造出這數字內所有範圍的數字 問說還要新增哪些數字
首先肯定先使用小的硬幣構造小的面額
[x x x x x ] -> [0, limit] 加入一x [x, limit+x]是否有相交
如果有相交代表limit + x這段都可以被構造出來 沒有的話代表 limit + 1可能就會遺漏 需新增進去
此時上線會變成 limit += limit+1
之後就不斷確認[x, 2*limit+2+x]是否有重疊到
*/
