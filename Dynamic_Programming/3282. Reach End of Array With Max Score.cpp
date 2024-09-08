/*
3282. Reach End of Array With Max Score
*/

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long findMaximumScore(vector<int>& nums) {
        int n = nums.size();
        LL res = 0;
        LL cur = nums[0];
        for(int i = 1; i < n; i++){
            res += cur;
            cur = max(cur, (LL)nums[i]);
        }
        
        return res;
    }
};


/*
[x0 x1 x2 x3 x4] idx = 5 跳到我的最大值 就會是 前面的數字 idx與之相減 * 前面數字 
越前面的數字相減越大 並且他越大越好
用數學的角度去理解(j - i) * nums[i]
一個數字跳到另一個數字 如果跳過去的數字沒有我大 我還不如不跳 所以可以發現會是貪心的跳到下個更大的數字 在此之前都是用自己的數字去累加
另一個角度是想到接雨水那題 也可以看出這個端倪
*/
