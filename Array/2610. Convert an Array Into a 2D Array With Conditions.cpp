/*
2610. Convert an Array Into a 2D Array With Conditions
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        unordered_map<int,int> map;
        for(auto x : nums){
            map[x] += 1;
        }

        vector<vector<int>> res;
       
        while (!map.empty()) {
            vector<int> temp;
            vector<int> toDelete;  // 用來保存要刪除的 key
            for (auto& p : map) {
                temp.push_back(p.first);
                p.second -= 1;
                if (p.second == 0) {
                    toDelete.push_back(p.first);
                }
            }
            for (int key : toDelete) {
                map.erase(key);
            }
            res.push_back(temp);
        }
        return res;
    }
};

//構造1d array 變成 2d array 每一row元素獨特 並且讓row盡量少 能夠怎麼構造
