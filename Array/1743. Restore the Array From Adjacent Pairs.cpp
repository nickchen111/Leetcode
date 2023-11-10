/*
1743. Restore the Array From Adjacent Pairs
*/

// TC:O(n) SC:O(2*V) 
class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        //Hash table
        int n = adjacentPairs.size();
        unordered_map<int,vector<int>> map;
        for(auto adj:adjacentPairs){
            map[adj[0]].push_back(adj[1]);
            map[adj[1]].push_back(adj[0]);
        } 
        vector<int> res;
        for(auto p:map){
            if(p.second.size() == 1){
                res.push_back(p.first);
                res.push_back(p.second[0]);
                break;
            }
        }

        //四個點只需三條邊的概念
        while(res.size() < n+1){
            int last = res[res.size()-1];
            int prev = res[res.size()-2];
            vector<int> candidates = map[last];
            int next = (candidates[0] == prev) ? candidates[1]:candidates[0];
            res.push_back(next);
        }

        return res;
    }
};
