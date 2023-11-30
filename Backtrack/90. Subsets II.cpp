/*
90. Subsets II
*/


//此題為subset新增一條件數組裡可能包含重複項且是尚未排序的狀態 要如何避免用到重複像排出一樣的subset是重點
// TC:O(2^n+ nlgn) SC:O(2^n)
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> track;
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtrack(nums, 0);

        return ans;
    }
    void backtrack(vector<int>& nums, int start){
        ans.push_back(track);

        for(int i = start; i < nums.size(); i++){
            if(i > start && nums[i] == nums[i-1]){//新增往回看的條件來判斷是否該使用
                continue;
            }
            track.push_back(nums[i]);
            backtrack(nums, i+1);
            track.pop_back();
        }

    }
};

/*
解題思路
切記去重的話都要先sort
子集問題新增需要去重的狀況 即為元素可重複但不可複選 所以需要新增條件特別判斷
*/
