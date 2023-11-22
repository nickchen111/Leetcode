/*
1424. Diagonal Traverse II
*/

// TC:O(n*m) SC:O(n*m)
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        map<int,vector<int>> map;
        for(int i=0; i<nums.size(); i++){
            for(int j = 0; j<nums[i].size(); j++){
                map[j+i].insert(map[j+i].begin(),nums[i][j]);
            }
        }
        vector<int> res;
        for(auto x:map){
            for(int i = 0; i < x.second.size(); i++){
                res.push_back(x.second[i]);
            }
        }

        return res;
    }
};

//用array取代hash table
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        vector<vector<int>> map;
        for(int i=0; i<nums.size(); i++){
            for(int j = 0; j<nums[i].size(); j++){
                if(map.size() <= i+j) map.push_back({});
                map[j+i].insert(map[j+i].begin(),nums[i][j]);
            }
        }
        vector<int> res;
        for(auto x:map){
            for(int i = 0; i < x.size(); i++){
                res.push_back(x[i]);
            }
        }

        return res;
    }
};
