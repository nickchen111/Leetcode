/*
2766. Relocate Marbles
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        unordered_map<int,int> map;
        for(auto x:nums){
            map[x] = 1;
        }

        int n = moveFrom.size();
        for(int i =0; i < n; i++){
            map.erase(moveFrom[i]);
            map[moveTo[i]] = 1;
        }

        vector<int> res;
        for(auto p : map){
            res.push_back(p.first);
        }
        sort(res.begin(), res.end());

        return res;
    }
};
