/*
3315. Construct the Minimum Bitwise Array II
*/

// TC:O(10*n) SC:O(1)
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,-1);
        
        
        for(int i = 0; i < n; i++) {
            if(nums[i] % 2 == 0) continue;
            
            int cur = nums[i];
            int count_one = 0;
            while(nums[i]%2) {
                count_one += 1;
                nums[i] >>= 1;
            }
            
            res[i] = (nums[i] << count_one) + (1 << (count_one-1)) - 1;
            
        }
        
        return res;
    }
};

/*
2 -> 10
6 -> 110 
3 -> 11 -> 01 | 10
5 -> 101
7 -> 111 -> 11 | 100
植樹看起來都會有最底的1
如果是2^x - 1 就可以用一半-1來去對應他 其他不可

47 -> 101111
39 -> 100111
*/
