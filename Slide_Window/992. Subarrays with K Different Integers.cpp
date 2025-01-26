/*
992. Subarrays with K Different Integers
*/

// 2025.01.26 三指針 one pass
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        int n = nums.size();
        int i1 = 0, i2 = 0, ans = 0, sum1 = 0, sum2 = 0;
        unordered_map<int,int> mp1, mp2;
        for(int j = 0; j < n; j++) {
            sum1 += (mp1[nums[j]]++ == 0);
            sum2 += (mp2[nums[j]]++ == 0);
            while(sum1 >= k) {
                sum1 -= (mp1[nums[i1++]]-- == 1);
            }
            while(sum2 >= k+1) {
                sum2 -= (mp2[nums[i2++]]-- == 1);
            }
            ans += (i1-i2);
        }
        return ans;
    }
};

// TC:O(n) SC:O(n)
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k-1);
    }
    int atMostK(vector<int>& nums, int k){
        unordered_map<int,int> map;
        int count = 0;
        int j = 0;
        for(int i = 0; i<nums.size(); i++){
            while(j <= nums.size() && map.size() <=k){
                if(j < nums.size()) map[nums[j]]+=1;
                count+=(j-i);
                j++;
            }
            
            map[nums[i]]-=1;
            if(map[nums[i]] == 0) map.erase(nums[i]);
        }

        return count;
    }
};
