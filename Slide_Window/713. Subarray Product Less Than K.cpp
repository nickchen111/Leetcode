/*
713. Subarray Product Less Than K
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int n = nums.size();
        if(k <= 1) return 0;
        int i = 0, ans = 0, sum = 1;
        for(int j = 0; j < n; j++) {
            sum *= nums[j];
            while(sum >= k) {
                sum /= nums[i++];
            }
            ans += j - i + 1;
        }
        return ans;
    }
};
/*
此題考點要乘法的特殊性導致如果找不到數字低於k的話 sum = 0 之後就都會錯 並且ｊ的位置也會在i前面
*/
