/*
2996. Smallest Missing Integer Greater Than Sequential Prefix Sum
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int missingInteger(vector<int>& nums) {
            int n = nums.size();
            unordered_set<int> set(nums.begin(),nums.end());
            int maxVal = nums[0];
            
            for(int i = 1; i < n; i++){
                if(nums[i] == nums[i-1] +1) maxVal += nums[i];
                else break;
            }
        
            
            while(set.find(maxVal) != set.end()){
                maxVal += 1;
            }
            
            return maxVal;
    }
};

/*
最長序列的總和 找到最小的不存在的數字 此數字可能等於或者大於序列總和
如果只有一個數字也可以算是sequential
*/
