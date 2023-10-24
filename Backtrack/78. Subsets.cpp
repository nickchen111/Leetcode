/*
78. Subsets
*/

//此題是求subset 排列出來的組合數字根據數組內的順序不能變 但特別的地方是他的深度是可以變化的
//一樣是backtracking的模板去根據做變化 tc: o(2^n) sc: (2^n)  其中 n 是待生成子集的整数数组的长度。
class Solution {
private:
    vector<vector<int>> ans;
    vector<int> track;
public:
    vector<vector<int>> subsets(vector<int>& nums) {

        backtrack(nums, 0);
        return ans;
    }
    void backtrack(vector<int>& nums, int start){
        ans.push_back(track);// base case 我大家都要
        //前序位置每個節點值都是我要的子集

        for(int i = start; i < nums.size(); i++){
            track.push_back(nums[i]);
            backtrack(nums, i+1);
            track.pop_back();
        }

    }
};

/*
解題思維
就是回溯套模板 求子集基本款代表我所有節點值都要 數上每個節點都要

回溯算法的时间复杂度通常是指数级的，原因在于它的每一步都会产生多个分支，这些分支代表了不同的选择。考虑一个具体的例子，
比如生成一个长度为 n 的整数数组的所有子集。在每个元素上，我们都面临两种选择：将它加入子集或者不加入子集。因此，总的可能性就是 2^n，这就是回溯算法的时间复杂度。

*/
