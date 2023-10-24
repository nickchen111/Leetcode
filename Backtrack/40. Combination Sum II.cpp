/*
40. Combination Sum II
*/

// 10/15 TC:O(2^n) SC:O(2^n)
class Solution {
    vector<vector<int>> res;
    vector<int> track;
    //不可重複選擇相同元素 但元素有可能重複給
public:
    vector<vector<int>> combinationSum2(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());

        backtrack(nums,target,0,0);
        return res;
    }

    void backtrack(vector<int>& nums, int target,int sum,int cur){
        if(sum > target) return;
        if(sum == target) {
            res.push_back(track);
            return;
        }

        for(int i = cur; i<nums.size(); i++){
            if(i>cur && nums[i] == nums[i-1]) continue;
            sum+=nums[i];
            track.push_back(nums[i]);
            backtrack(nums,target,sum,i+1);
            sum-=nums[i];
            track.pop_back();
        }
    }
};
//用set的方式去除duplicate 以免出現重複的答案
class Solution1 {
public:
    void  dfs(vector<int> & candidates, int next, vector<int> temp, int target, set<vector<int>>& result){
        if(target == 0){
            result.insert(temp);
            return;
        }
        for(int i = next; i < candidates.size(); i++){
            if(candidates[i] > target) break; //因為有sort過，後面的也不用做了直接break
            temp.push_back(candidates[i]);
            dfs(candidates, i+1, temp, target - candidates[i], result );  // i代表next 繼續用相同的元素去做dfs
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        set<vector<int>> result;
        vector<int> temp;
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, temp, target, result);

        return vector<vector<int>>(result.begin(), result.end());
    }
};


//la大套路去解
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> track;
    int tracksum = 0;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0);

        return ans;
    }
    void backtrack(vector<int>& candidates, int target, int start){
        if(tracksum == target){
            ans.push_back(track);
            return;
        }
        if(tracksum > target) return;

        for(int i = start; i < candidates.size(); i++){
            if(i > start && candidates[i] == candidates[i-1]){
                continue;
            }
            tracksum += candidates[i];
            track.push_back(candidates[i]);
            backtrack(candidates, target, i+1);
            tracksum -= candidates[i];
            track.pop_back();
        }
    }
};

/*
解題思路

組合題 跟子集很像 说这是一个组合问题，其实换个问法就变成子集问题了：请你计算 candidates 中所有和为 target 的子集。
有給定目標值 所以base case即達到目標值 超過的話可直接return
有一關鍵 數組裡可能會有重複項 所以需去重 剩下的就是套模板
不能重複使用 所以要有start去控管

time: o(n!) or o (2^n)
space: o(n * 2 ^ n) o(kn)!?
*/

