/*
1695. Maximum Erasure Value
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        unordered_map<int,int> map;
        int sum = 0;
        int res = 0;
        int n = nums.size();
        int j = 0;
        for(int i = 0; i < n; i++){
            while(j < n && map.find(nums[j]) == map.end() ){
                map[nums[j]] +=1;
                sum += nums[j];
                res = max(res, sum);
                j++;
            }
            sum -= nums[i];
            map[nums[i]]-=1;
            if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return res;
    }
};

/*
此題簡單來說就是在問哪個子數組總和最大 子數組內每個元素都要是Unique
*/
