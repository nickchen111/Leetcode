/*
47. Permutations II
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]

Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Constraints:
1 <= nums.length <= 8
-10 <= nums[i] <= 10
*/



#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;


//permutation的變形題 除了要考慮遞迴時不能用到自己(需再從i = 0 迴圈頭出發找 所以需要考慮不能用自己) 還要考慮到用到重複使用同樣的數字去做排列組合
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> result;
        unordered_set<int> set;
        vector<int> temp;
        sort(nums.begin(), nums.end());
        dfs(nums, set, result, temp);
        return result;
    }
    void dfs(vector<int>& nums, unordered_set<int> set, vector<vector<int>>& result, vector<int> temp){
        for(int i = 0; i < nums.size(); i++){
            if(set.size() == nums.size()){
                result.push_back(temp);
                return;
            }
            //兩步去重
            if(set.find(i) != set.end()) continue; // 防止重複使用自己（自己已經在temp裡了）
            if(i > 0 && nums[i] == nums[i-1] && set.find(i-1) == set.end()) continue;
            //防止重複使用同樣的數字去做排列組合 -->會出現重複的排列組合
            temp.push_back(nums[i]);
            set.insert(i);
            dfs(nums, set, result, temp);
            temp.pop_back();
            set.erase(i);
        }
    }
};


//按照la的邏輯寫一次
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> track;
    bool* used;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        used = new bool[nums.size()]();
        sort(nums.begin(), nums.end());
        backtrack(nums);

        return ans;
    }
    void backtrack(vector<int>& nums){
        //確認停止條件
        if(track.size() == nums.size()){
            ans.push_back(track);
            return;
        }

        for(int i = 0; i < nums.size(); i++){
            if(used[i]) continue;

            if(i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

            track.push_back(nums[i]);
            used[i] = true;
            backtrack(nums);
            track.pop_back();
            used[i] = false;
        }
    }
};

/*
排列問題 套用模板 需use數組確認是否加入到track數組中了
此題有重複項 除了需要sort 還需要特殊條件去重（因為是排列題注重順序）：如果重複了 他的上一項跟他重複的還沒用過 你就不准用
*/

//la大的
class Solution {
public:
    // 保存结果
    vector<vector<int>> res;
    // 记录当前位置的元素
    vector<int> track;
    // 记录元素是否被使用
    vector<bool> used;

    // 主函数
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        // 排序，让相同的元素靠在一起
        sort(nums.begin(), nums.end());
        // 初始化used数组
        used = vector<bool>(nums.size(), false);
        // 回溯
        backtrack(nums);
        // 返回结果
        return res;
    }

    // 回溯函数
    void backtrack(vector<int>& nums) {
        // 当长度相等时，将结果记录
        if (track.size() == nums.size()) {
            res.push_back(track);
            return;
        }

        // 遍历没有被使用过的元素
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) {
                continue;
            }
            // 新添加的剪枝逻辑，固定相同的元素在排列中的相对位置
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) {
                continue;
            }
            // 添加元素，标记为使用过
            track.push_back(nums[i]);
            used[i] = true;
            // 继续回溯
            backtrack(nums);
            // 回溯
            track.pop_back();
            used[i] = false;
        }
    }
};