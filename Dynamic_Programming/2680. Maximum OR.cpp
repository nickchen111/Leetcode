/*
2680. Maximum OR
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumOr(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffix(n+1);
        for(int i = n-1; i >= 0; i--){
            suffix[i] = suffix[i+1] | (LL)nums[i];
        }

        LL prefix = 0;
        LL res = 0;
        for(int i = 0; i < n; i++){
            res = max(res, prefix | ((LL)nums[i] << k) | suffix[i+1]);
            prefix |= (LL)nums[i];
        }

        return res;
    }
};

/*
要構造出把nums 所有數字 OR後最大 並且可以操作 k次 *2
貪心的想要讓某個位階高的數字 但是要選哪個呢 會想選空缺
long long可以到2＾53次方 所以可以操作

每個數字都去嘗試 然後看前後面在每個位階上有哪些數字
大概25位階
如果太鑽牛角尖去想說 一定要找出一個最適合的 但是在找的時候你就是在判斷前後每個位階的1的位置
如果說你打算用構造的也是可以 那就會是25*n的時間 也就是用兩個數組紀錄前後每個位置1的所在 然後把他跑25loop構建起來
這樣何不乾脆遍歷嘗試一遍呢
*/
