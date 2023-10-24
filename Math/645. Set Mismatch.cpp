/*
645. Set Mismatch
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);//因為是從1~n的數字

        //遍歷確定每個數字都在正確位置
        for(int i = 1; i<=n; i++){
            //前項確認是不相同 想將它放在正確位置上 中項確認不越界 但這題肯定不會越界 後項確認換過去的value跟目前不相同
            while(nums[i] != i && nums[i] <=n && nums[i] != nums[nums[i]]){
                swap(nums[i], nums[nums[i]]);
            }
        }

        for(int i = 1; i<=n;i++){
            if(nums[i] != i){
                return {nums[i],i};
            }
        }

        return {-1,-1};//無意義的數字
    }
};
/*
HG: 算是445, 448的綜合題目
要找missing 跟duplicate number
*/
