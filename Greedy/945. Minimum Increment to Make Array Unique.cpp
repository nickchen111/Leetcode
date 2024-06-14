/*
945. Minimum Increment to Make Array Unique
*/


// Greedy TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        int res = 0;
        int need = 0;
        for(int i = 0; i < n; i++){
            res += max(need-nums[i],0);
            need = max(need, nums[i]) + 1;
        }

        return res;
    }
};


// UF TC:O(n) SC:O(n)
class Solution {
public:
    unordered_map<int, int> root;
    int minIncrementForUnique(vector<int>& A) {
        int res = 0;
        for (int a : A)
            res += find(a) - a;
        return res;
    }
    int find(int x) {
        return root[x] = root.count(x) ? find(root[x] + 1) : x;
    }
};
