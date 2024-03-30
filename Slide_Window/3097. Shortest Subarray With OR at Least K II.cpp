/*
3097. Shortest Subarray With OR at Least K II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        
        
        vector<int> count(32);
        if(k == 0) return 1;
        int len = INT_MAX;
        int i = 0;
        int curVal = 0;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 32; k++){
                int tmp = (nums[j]>>k)&1;
                if(tmp) count[k] += 1; 
                if(count[k] == 1){
                    curVal |= (1<<k);
                }
            }
            
            while(i < n && curVal >= k){
                len = min(len, j-i+1);
                for(int k = 0; k < 32; k++){
                    if(!count[k]) continue;
                    int tmp = (nums[i]>>k)&1;
                    if(tmp){
                        count[k] -= 1;
                        if(count[k] == 0){
                            curVal -= (1<<k);
                        }
                    }
                }
                i++;
            }
        }
        
        return len == INT_MAX ? -1 : len;
    }
};
