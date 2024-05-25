/*
3159. Find Occurrences of an Element in an Array
*/

// TC:O(m+n) SC:O(n)
class Solution {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {
        unordered_map<int, vector<int>> map;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            map[nums[i]].push_back(i);
        }
        int m = queries.size();
        vector<int> res(m,-1);
        for(int i = 0; i < m; i++){
            int count = queries[i];
            if(map[x].size() < count) continue;
            else res[i] = map[x][count-1];
        }
        
        return res;
    }
};
