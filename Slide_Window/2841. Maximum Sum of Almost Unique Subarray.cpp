/*
2841. Maximum Sum of Almost Unique Subarray
*/

// TC:O(n) SC:O(m)
class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
        long long res = 0;
        long long sum = 0;
        int n = nums.size();
        unordered_map<int,int> map;
        int j = 0;
        for(int i = 0; i < n; i++){
           while(j < n && j - i + 1 <= k){
               sum += nums[j];
               map[nums[j]]+=1;
               if(j - i + 1 == k && map.size() >= m){
                   res = max(res, sum);
               }
               j++;
           }
           //為了j == n 而出來的case
           if(j - i + 1 == k && map.size() >= m){
                    res = max(res, sum);
           }
           sum -= nums[i];
           map[nums[i]] -= 1;
           if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return res;
    }
};

/*
此題題意為給一數組 符合條件 至少要有m種元素 且長度為k的最大總和 
如果沒有此種數組 返回0
*/
