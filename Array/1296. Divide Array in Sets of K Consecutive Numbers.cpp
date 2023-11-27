/*
1296. Divide Array in Sets of K Consecutive Numbers
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        unordered_map<int,int> map;
        int n = nums.size();
        if(n%k != 0) return false;
        for(auto num:nums){
            map[num]+=1;
        }
        
        for(int i = 0; i<n; i++){
            if(map[nums[i]] == 0) continue;
            map[nums[i]]-=1;

            for(int j = 1; j<k; j++){
                if(map[nums[i]+j] == 0) return false;

                map[nums[i]+j]-=1;
            }
        }

        return true;
    }
};
