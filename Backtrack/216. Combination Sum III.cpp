/*
216. Combination Sum III
*/

// TC:O(2^k) SC:O(k)
class Solution {
    vector<int> nums = {1,2,3,4,5,6,7,8,9};
    vector<vector<int>> res;
    vector<int> track;
    //此題限制 只能用k個數字達成目標 只能用1~9的範圍且一個數字只能用一次
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtrack(k,n, 0,0);

        return res;
    }

    void backtrack(int k, int n, int cur, int sum){
        if(sum == n && track.size() == k) {
            res.push_back(track);
            return;
        }
        if(track.size() > k || sum > n) return;
        for(int i = cur; i<nums.size(); i++){
            sum+=nums[i];
            track.push_back(nums[i]);
            backtrack(k,n,i+1,sum);
            sum-=nums[i];
            track.pop_back();
        }
    }
};
