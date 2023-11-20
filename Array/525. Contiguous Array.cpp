/*
525. Contiguous Array
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        //此題將0想成-1 1想成+1 求最長的sum為零的subarray
        unordered_map<int,int> map; // presum->index;
        map[0] = -1;//如果對到所有區間加總都是0
        int presum = 0;
        int res = 0;
        for(int i = 0; i<nums.size(); i++){
            if(nums[i] == 0) presum-=1;
            else if(nums[i] == 1) presum+=1;

            if(map.find(presum) != map.end()){
                res = max(res, i-map[presum]);
            }
            else map[presum] = i;
        }

        return res;

    }
};
