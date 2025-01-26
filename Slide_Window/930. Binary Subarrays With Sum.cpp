/*
930. Binary Subarrays With Sum
*/

// 2025.01.26 兩種寫法 1. 三指針 2.兩次滑窗
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size(); 
        int i1 = 0, i2 = 0, sum1 = 0, sum2 = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            sum1 += nums[j];
            sum2 += nums[j];
            while(sum1 >= goal && i1 <= j) {
                sum1 -= nums[i1++];
            }
            while(sum2 >= goal+1 && i2 <= j) {
                sum2 -= nums[i2++];
            }
            ans += i1-i2;
        }
        return ans;
    }
};

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int n = nums.size(); 
        auto atLeastK = [&](int k) -> int {
            int i = 0, sum = 0, ans = 0;
            for(int j = 0; j < n; j++) {
                sum += nums[j];
                while(i <= j && sum >= k) {
                    sum -= nums[i++];
                }
                ans += i;
            }
            return ans;
        };
        return atLeastK(goal) - atLeastK(goal+1);
    }
};

// Hash + Presum TC:O(n) SC:O(n)
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int,int> map; // prefix -> count of index 
        map[0] = 1;
        int presum = 0;
        int res = 0;
        for(int i = 0; i<nums.size(); i++){
            presum+=nums[i];
            if(map.find(presum-goal) != map.end()){
                res+=map[presum-goal];
                map[presum]+=1;
            }
            else map[presum]+=1;
        }

        return res;
    }
};
