/*
2044. Count Number of Maximum Bitwise-OR Subsets
*/

// TC:O(2^n) SC:O(n)
class Solution {
    int mx;
    int res = 0;
    int n;
    vector<int> nums;
public:
    int countMaxOrSubsets(vector<int>& nums) {
        n = nums.size();
        this -> nums = nums;
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum |= nums[i];
        }
        mx = sum;

        backtrack(0, 0);

        return res;
    }
    void backtrack(int total, int cur) {
        if(total == mx) {
            res += (1 << (n-cur));
            return;
        }

        if(cur == n) return;

        backtrack(total, cur+1);
        backtrack(total | nums[cur], cur+1);
    }
};
