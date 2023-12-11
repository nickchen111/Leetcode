/*
2874. Maximum Value of an Ordered Triplet II
*/

// TC:O(3*n) SC:O(2*n)
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix(n);
        vector<int> suffix(n);
        int maxNum = INT_MIN;
        for(int i = 0; i < nums.size(); i++){
            maxNum = max(maxNum, nums[i]);
            prefix[i] = maxNum;
        }
        maxNum = INT_MIN;
        for(int i = n-1; i >=0; i--){
            maxNum = max(maxNum, nums[i]);
            suffix[i] = maxNum;
        }
        long long res = 0;
        for(int i = 1; i < n-1; i++){
            long long a = prefix[i-1], b = nums[i], c = suffix[i+1];
            res = max(res, (a-b)*c);
        }

        return res;
    }
};

/*
此題要找個 三個數字讓 (nums[i] - nums[j]) * nums[k] 盡量大  s.t i < j < k
nums[i]盡量大 nums[j]盡量小 nums[k]盡量大
prefix[i] i之前最大的 suffix[i]之後最大的 並且對於每個點都當他是最小 找 他前面最大跟後面最大
*/
