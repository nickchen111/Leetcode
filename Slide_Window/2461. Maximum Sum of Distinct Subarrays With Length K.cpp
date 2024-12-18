/*
2461. Maximum Sum of Distinct Subarrays With Length K
*/

// 1119 TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0;
        LL sum = 0;
        LL res = 0;
        unordered_map<int,int> map;
        for(int j = 0; j < n; j++) {
            sum += nums[j];
            map[nums[j]] += 1;
            if(j - i + 1 == k) {
                if(map.size() == k) {
                    res = max(res, sum);
                }
                map[nums[i]] -= 1;
                sum -= nums[i];
                if(map[nums[i]] == 0) map.erase(nums[i]);
                i++;
            }
        }

        return res;
    }
};

// TC:O(n) SC:O(n)
class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long res = 0;
        int n = nums.size();
        int j = 0;
        unordered_map<int,int> map;
        long long sum = 0;
        for(int i = 0; i<n; i++){
            while(j < n && map[nums[j]] == 0 && map.size() <= k){
                sum+=nums[j];
                map[nums[j]]+=1;
                if(map.size() == k)
                    res = max(res, sum);
                j++;
            }

            map[nums[i]]-=1;
            sum-=nums[i];
            if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return res;
    }
};

/*
此題限制
1.長度必須為k 
2.所有數字必須是獨特的 找出unique方法 判斷容器內是否出現過 似2747題
*/
