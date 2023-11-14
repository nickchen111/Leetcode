/*
47. Permutations II
*/

// TC: O(n!)  SC: O(n!)
class Solution {
    vector<vector<int>> res;
    vector<int> track;
    vector<bool> visited;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        visited = vector<bool>(nums.size(),0);
        sort(nums.begin(),nums.end());
        backtrack(nums);

        return res;
    }

    void backtrack(vector<int>& nums){
        if(track.size() == nums.size()){
            res.push_back(track);
            return;
        }

        for(int i = 0; i<nums.size(); i++){
            if(visited[i] == true) continue;
            if(i && nums[i] == nums[i-1] && visited[i-1] == 0) continue;
            track.push_back(nums[i]);
            visited[i] = true;
            backtrack(nums);
            track.pop_back();
            visited[i] = false;
        }
    }
};

//unordered_set去重 
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



/*
排列問題 套用模板 需use數組確認是否加入到track數組中了
此題有重複項 除了需要sort 還需要特殊條件去重（因為是排列題注重順序）：如果重複了 他的上一項跟他重複的還沒用過 你就不准用
*/

//la
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
