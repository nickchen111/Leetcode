/*
3026. Maximum Good Subarray Sum
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<LL> presum(n);
        for(int i = 0; i < n; i++){
            presum[i] = (i-1 < 0 ? 0 : presum[i-1]) + nums[i];
        }
        
        unordered_map<LL,LL> map; // 走到的數字 -> presum
        
        LL res = LLONG_MIN;//如果沒有要回傳0
        for(int i = 0; i < n; i++){
            LL cur = presum[i];
            if(map.find(nums[i]-k) != map.end()){
                LL prevSum = map[nums[i]-k] - (nums[i]-k);
                res = max(res, cur - prevSum);
            }
            if(map.find(nums[i]+k) != map.end()){
                LL prevSum = map[nums[i]+k] - (nums[i]+k);
                res = max(res, cur - prevSum);
            }
            // 更新map 
            if(map.find(nums[i]) != map.end()){
                if(map[nums[i]] < cur) continue;
                else map[nums[i]] = cur;
            }
            else map[nums[i]] = cur;
        }
        
        return res == LLONG_MIN ? 0 : res;
        
    }
};


/*
這題問說要找出滿足以下條件的subarray之中最大的和可以是多少
|nums[i] - nums[j]| == k
-k == nums[i] - nums[j] == k
nums[i] = nums[j] -k || nums[j] + k;
ex : i = 2, k = 3, j = 5 or -1
這題就是去想說將每個字都當成最尾端元素那麼他能構造出的最大和有多少
可以用一個map紀錄走過的數字有哪些從這些數字中挑出presum最小的紀錄起來即可
*/
