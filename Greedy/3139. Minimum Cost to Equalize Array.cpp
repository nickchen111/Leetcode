/*
3139. Minimum Cost to Equalize Array
*/

// TC:O(m+n + nlgn) m 為 當下最大值 n 為數組長度 SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2) {
        int  n = nums.size();
        sort(nums.begin(), nums.end());
        LL total = accumulate(nums.begin(), nums.end(), 0LL);
        if(n == 1) return 0;

        if(n == 2){
            return ((LL)(nums[1] - nums[0])*(LL)cost1) % M;
        }

        if(cost2 >= cost1*2){
            LL diff = 0;
            for(int i = 0; i < n; i++){
                diff += (nums.back() - nums[i]);
            }

            return (diff*cost1)% M;
        }
        

        int m = nums.back();
        LL ret = LLONG_MAX;
        for(int limit = m; limit <= 2*m; limit++){
            LL diff0 = limit - nums[0];
            LL diff_total = (LL)limit*n - total;
            LL res;
            // majority
            if(diff0 > diff_total/2){
                res = ((diff_total - diff0) * (LL)cost2) + ((diff0 - (diff_total - diff0))* (LL)cost1);
            }
            else {
                res = (diff_total/2)*(LL)cost2 + (diff_total%2 == 1 ? cost1 : 0);
            }

            ret = min(ret, res);
        }

        return ret % M;
    }
};


/*
每次可以選某一個操作
選一個元素 + 1, cost1 
選兩個元素位置 i, j 必須不同位置+1, cost2
問說最少cost 讓所有元素相同

首先如果cost2 > cost1*2 就不用他
後面的數看可以做幾次兩次操作 讓他們可以快速上升到target
後面的樹的diff取出來 然後看說最大的數字freq 
這題就轉變成如何讓他們瘋狂消 

Boyer Moore 
不需要用一個容器空間n去裝所有數字 只需要用兩個變數
a, b 遇到不同的就分別裝在a or b 然後開始去消掉 優先找多的那個容器消掉，如果有majority 那兩個容器之一肯定會剩下元素

最難的問題就是 那上限需要提升到多少？ 不能用二分 因為可能會呈現U型分佈 並不是一個單調的
-> 只需要把上限拉高一倍就好 ， 這樣的話原本是majority的那項在 n >= 3 的狀況就不可能會是majority
想到這個的方式也是從數據規模 1 <= nums[i] <= 10^6

*/
