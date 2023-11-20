/*
1004. Max Consecutive Ones III
*/

// 固定左邊界 手動拓展右邊界 TC:O(n) SC:O(1)
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int count = 0;
        int j = 0;
        int res = 0;
        for(int i=0; i<nums.size(); i++){
            while( j < nums.size() && (nums[j] == 1 || count <= k)){
                if(nums[j] == 1){
                    res = max(res,j-i+1);
                }
                else if(nums[j] == 0){
                    count++;
                    if(count > k){
                        count--;
                        break;
                    }
                    else res = max(res,j-i+1);
                }
                j++;
            }
            if(nums[i] == 0) count-=1;
        }

        return res;
    }
};

//固定右邊界 
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        //遍歷右邊界寫法 
        int res = 0; int count = 0; int i = 0;
        for(int j = 0; j<nums.size(); j++){
            if(nums[j] == 1){
                res = max(res,j-i+1);
            }
            else if(nums[j] == 0){
                count++;
                while(count > k){
                    if(nums[i] == 0){
                        count-=1;
                    }
                    i++;
                }
                res = max(res,j-i+1);
            }
        }

        return res;
    }
};
