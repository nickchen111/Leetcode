/*
  3065. Minimum Operations to Exceed Threshold Value I
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int count = 0;
        for(auto x : nums){
            if(x < k) count += 1;
        }
        
        return count;
        
        
    }
};

/*每一次操作可以消掉最小元素 問說最少需要幾次讓所有元素大於等於k
*/
