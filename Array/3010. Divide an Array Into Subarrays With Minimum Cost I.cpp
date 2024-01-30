/*
3010. Divide an Array Into Subarrays With Minimum Cost I
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int res = nums[0];
        int start = nums[0];
        sort(nums.begin(), nums.end());
        bool flag = 0;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(flag == 0 && nums[i] == start){
                flag = 1;
                continue;
            }
            else {
                res += nums[i];
                count += 1;
            }
            if(count == 2) break;
        }
        
        return res;
    }
};

// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int n = nums.size();
        int res = INT_MAX;
        for(int i = 1; i < n; i++){
            for(int j = i+1; j < n; j++){
                res = min(res,nums[i] + nums[j] + nums[0]);
            }
        }
        
        return res;
    }
};

/*
要你切割數組成三等份 然後用切割後的數組第一個數字當作此數組代表 問最小總和為多少 
固定第一個必須是第一等分的數組的頭 brute force找後面兩個頭
*/
