/*
2750. Ways to Split Array Into Good Subarrays
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfGoodSubarraySplits(vector<int>& nums) {
       long long res = 1;
       long long M = 1e9+7;
       int i = 0; 
       while( i < nums.size() && nums[i] == 0 ) i++;
       if(i == nums.size()) return 0;
       int count = 0;
       while( i < nums.size()){
           if(nums[i] == 1){ 
               res = (res%M * (count+1))%M;
               count = 0;
            }
           else count++;
           i++;
       }

       return res;
    }
};

/*
此題題意為要將一個數組分成每個子數組都只有一個1的分割方式有幾種
左邊的leading zero完全不會影響結果計算 因為一定是被第一個1包起來
之後開始計算1與1之間0的個數 然後再找下一對1與1 將答案相乘
*/
