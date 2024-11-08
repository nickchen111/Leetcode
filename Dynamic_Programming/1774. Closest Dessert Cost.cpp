/*
1774. Closest Dessert Cost
*/

// TC:O(m*n*sum) SC:O(1)
class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {

        int n = baseCosts.size();
        int m = toppingCosts.size();
        int res = INT_MAX;
        
        // TC:O(m*n*sum) SC:O(1)
        function<void(int, int)> dfs = [&](int i, int sum) -> void {
            int curDiff = abs(sum - target);

            if(curDiff < abs(res - target) || (abs(res - target) == curDiff && res > sum) ) {
                res = sum;
            } 

            if(i < 0 || sum >= target) {
                return;
            }

            dfs(i - 1, sum);
            dfs(i - 1, sum + toppingCosts[i]);
            dfs(i - 1, sum + toppingCosts[i] * 2);
        };

        for(int i = 0; i < n; i++) {
            dfs(m-1, baseCosts[i]);
        }

        return res;
    }
};


/*
終於看懂 basecosts只能選一種 toppingCosts 每一個只能最多選兩個但不同種類可以選很多個沒差 問說 abs 最接近target的成本是?
*/
