/*
1749. Maximum Absolute Sum of Any Subarray
*/

// TC:O(n) SC:O(1) DP思想 Kadane 
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        
        int mx = 0;
        int mn = 0;

        int res = INT_MIN;
        for(int i = 0; i < n; i++){
            mx = max(nums[i], mx + nums[i]);
            mn = min(nums[i], mn + nums[i]);
            res = max(res, abs(mx));
            res = max(res, abs(mn));
        }
        return res;
    }
};

// presum 思想
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        
        int presum_max = 0;
        int presum_min = 0;

        int prefix = 0;
        for(int i = 0; i < n; i++){
            prefix += nums[i];
            presum_max = max(presum_max, prefix);
            presum_min = min(presum_min, prefix);

        }
        return presum_max - presum_min;
    }
};

/*
此題想求一數組內最大總和subarray為多少 跟之前的題目挺類似 例如用slide window解 或者deque + presum
但這題多加個條件是可以允許絕對值 -> 跟152題很像！
如果沒有的話 只包含負數 那就會想找presum最負的時候跟最正的時候兩個相減為答案

*/
