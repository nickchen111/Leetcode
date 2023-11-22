/*
2831. Find the Longest Equal Subarray
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, vector<int>> map;
        for(int i = 0; i<nums.size(); i++){
            map[nums[i]].push_back(i);
        }
        int res = 0;
        for(auto [val,pos]:map){
            int j = 0;
            for(int i = 0; i<pos.size(); i++){
                while(j <pos.size() && pos[j]-pos[i]+1-(j-i+1) <= k){
                    j++;
                }
                res = max(res, j-i);
            }
        }

        return res;
    }
};

/*
紀錄每個數字的idx 排序頻率 從idx開始跳
[x x [2 x x 2 x x] x 2 x x x x 2]
pos[j]-pos[i]+1 -(j-i+1) <= K
                合法的數量
*/
