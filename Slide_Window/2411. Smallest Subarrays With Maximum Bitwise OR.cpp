/*
2411. Smallest Subarrays With Maximum Bitwise OR
*/

// TC:O(96*n) SC:O(32)
class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> count(32,0);
        int j = n-1;
        vector<int> res(n);
        for(int i = n-1; i>=0; i--){
            for(int k = 0; k<32; k++){
                count[k]+=((nums[i]>>k)&1);
            }
            while(j > i && isOkRemove(nums[j],count)){
                for(int k =0; k<32; k++){
                    count[k]-=((nums[j]>>k)&1);
                }
                j--;

            }
            res[i] = j-i+1;
        }
        return res;
    }

    bool isOkRemove(int num, vector<int>& count){
        for(int i = 0; i<32; i++){
            if(count[i] == 1 && ((num>>i)&1)) return false;
        }
        return true;
    }
};
/*
以每個元素作為左邊界 去找右邊的subarray使他的OR運算盡量大 但是subarray盡量短
要從最右邊開始做 這樣才不用重複做 時間複雜度才會是線性
*/
