/*
39. Combination Sum
*/

//此題給一數組與target 問說 哪些數字加起來可以等於target 可以用重複的相同數字 但是不需要給一樣的數字串 ex 2 2 3, 3,2,2

//backtrack TC:O(2^n) SC:O(2^n) 看這就好
class Solution {
    vector<vector<int>> res;
    vector<int> track;
    //可重複選擇一樣的元素 
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
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
            
            sum+=nums[i];
            track.push_back(nums[i]);
            backtrack(nums,target,sum,i);
            sum-=nums[i];
            track.pop_back();
        }
    }
};

//用recursion 結構有點dfs的感覺 tc: o(n!) or o(2 ^ n) space: o(2^n)
class Solution {
public:
    void  backtracking(vector<int> & candidates, int next, vector<int> temp, int target, vector<vector<int>>& result){
        if(target == 0){
            result.push_back(temp);
            return;
        }
        if(next == candidates.size() || target - candidates[next] < 0) return;

        temp.push_back(candidates[next]);
        backtracking(candidates, next, temp, target - candidates[next], result);
        temp.pop_back();
        backtracking(candidates, next+1, temp, target, result);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, 0, temp, target, result);

        return result;


        
    }
};

//from huahua的寫法 寫得更像dfs 感覺更可以去處理其他種變形題
class Solution2 {
public:
    void  dfs(vector<int> & candidates, int next, vector<int> temp, int target, vector<vector<int>>& result){
        if(target == 0){
            result.push_back(temp);
            return;
        }
        for(int i = next; i < candidates.size(); i++){
            if(candidates[i] > target) break; //因為有sort過，後面的也不用做了直接break
            temp.push_back(candidates[i]);
            dfs(candidates, i, temp, target - candidates[i], result );  // i代表next 繼續用相同的元素去做dfs
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, temp, target, result);

        return result;


        
    }
};
