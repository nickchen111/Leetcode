/*
1863. Sum of All Subset XOR Totals
*/

// TC:O(2^n) SC:O(n)
class Solution {
    int res = 0;
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n; i++){
            vector<bool> visited(n);
            visited[i] = 1;
            Backtrack(visited, nums, nums[i], i);
            visited[i] = 0;
        }

        return res;
    }
    void Backtrack(vector<bool>& visited, vector<int>& nums, int cur, int idx){
        res += cur;
        for(int i = idx+1; i < nums.size(); i++){
            if(visited[i]) continue;
            visited[i] = 1;
            Backtrack(visited, nums, cur ^ nums[i],i);
            visited[i] = 0;
        }
    }
};
