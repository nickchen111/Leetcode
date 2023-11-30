/*
77. Combinations
*/


//此題很像permutation 但是結合了subset的只往前走限制 但只收集固定長度的排列組合
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums;
        for(int i = 1; i <= n; i++){
            nums.push_back(i);
        }
        vector<int> temp;
        vector<vector<int>> result;
        int next;
        dfs(nums, 0, k, temp, result);
        
        return result;
    }
    void dfs(vector<int> nums, int next, int k, vector<int> temp, vector<vector<int>>& result){
        if(temp.size() == k){
            result.push_back(temp);
            return;
        }
        for(int i = next; i < nums.size(); i++){
            temp.push_back(nums[i]);
            dfs(nums, i+1, k, temp, result);
            temp.pop_back();
        }
    }
};

//其實可以不用特別開一個vector來記錄數組  tc: o(c(n,k) * k)  space: o(k)
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> temp;
        vector<vector<int>> result;
        int next;
        dfs(n, 1, k, temp, result);
        
        return result;
    }
    void dfs(int n, int next, int k, vector<int> temp, vector<vector<int>>& result){
        if(temp.size() == k){
            result.push_back(temp);
            return;
        }
        for(int i = next; i < n+1; i++){
            temp.push_back(i);
            dfs(n, i+1, k, temp, result);
            temp.pop_back();
        }
    }
};

//labu大方法在寫一次
class Solution {
private:
    vector<int> track;// 路徑紀錄
    vector<vector<int>> ans;//結果
public:
    vector<vector<int>> combine(int n, int k) {
        backtrack(n, k, 1);
        return ans;
    }
    void backtrack(int n, int k, int start){
        if(track.size() == k){//base case 結束條件
            ans.push_back(track);
            return;
        }

        for(int i= start; i <= n; i++){//回溯是著重在edge所以backtrack會寫在for loop內
            track.push_back(i);
            backtrack(n, k, i+1);
            track.pop_back();
        }
    }
};

/*
解題思維
組合排列子集都可以靠回溯解答
此題要求的是子集中某一層的結果改一下base case就好 即k層

*/
