/*
46. Permutations
*/


//此題為無重複的數組 想求給定你任一數組後 其排列組合有多少種 ex 123 有九種可能 

//la大 思路實作
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> track; //記錄路徑 類似graph的visited功能
        vector< bool> used(nums.size(), false);

        backtrack(nums, track, used, ans);
        return ans;
    }
    void backtrack(vector<int>& nums, vector<int>& track, vector< bool>& used,vector<vector<int>>& ans){
        if(track.size() == nums.size()) {
            ans.push_back(track);
            return;
        }
        for(int i=0; i < nums.size(); i++){
            if(used[i]) continue;
            track.push_back(nums[i]);
            used[i] = true;
            backtrack(nums, track, used, ans);
            track.pop_back();
            used[i] = false;
        }
    }
};

//TC:O(n!) SC:O(n)
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> track;
    bool* used;
    vector<vector<int>> permute(vector<int>& nums) {
        used = new bool[nums.size()](); //()來初始化

        backtrack(nums);

        return ans;
    }
    void backtrack(vector<int>& nums){
        if(track.size() == nums.size()){
            ans.push_back(track);
            return;
        }

        for(int i = 0; i < nums.size(); i++){

            if(used[i]) continue;

            track.push_back(nums[i]);
            used[i] = true;
            backtrack(nums);
            track.pop_back();
            used[i] = false;
        }
    }
};

/*
解題思維：
全排列問題， 在乎順序 順序不同也是不一樣的答案->會走回頭路 所以要用used來紀錄數組中已經有的
*/

/*
解題思路
解决一个回溯问题，实际上就是一个决策树的遍历过程，站在回溯树的一个节点上，你只需要思考 3 个问题：

1、路径：也就是已经做出的选择。

2、选择列表：也就是你当前可以做的选择。

3、结束条件：也就是到达决策树底层，无法再做选择的条件。

*/
