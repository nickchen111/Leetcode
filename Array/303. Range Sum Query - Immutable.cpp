/*
303. Range Sum Query - Immutable
*/

//TC: O(n) SC:O(n)
class NumArray {
vector<int> presum;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        presum = vector<int>(n+1);
        //建立presum數組
        for(int i = 1; i<=nums.size(); i++){
            presum[i] = presum[i-1] + nums[i-1];
        }
    }
    
    int sumRange(int left, int right) {
        return presum[right+1] - presum[left];
    }
};


 /*
 此題為前綴和相關題 
 需畫出nums 跟presum之間index差別會比較好寫code
 1. 畫出or想出nums presum數組圖像 
 2. 建立presum數組
 3. 判斷題目要求的範圍 利用presum 相減得出

 tc: o(n) sc:o(n)
 */
