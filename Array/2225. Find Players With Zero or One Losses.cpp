/*
2225. Find Players With Zero or One Losses
*/

// TC:O(nln) SC:O(n)
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        map<int,int> indegree;
        for(auto &match : matches){
            indegree[match[1]] += 1;
        }
        for(auto &match : matches){
            if(indegree.find(match[0]) == indegree.end()){
                indegree[match[0]] = 0;
            }
        }
        vector<vector<int>> res(2);
        
        for(auto &x : indegree){
            if(indegree[x.first] == 1) res[1].push_back(x.first);
            if(indegree[x.first] == 0) res[0].push_back(x.first);
        }

        return res;
    }
};

/*
給你一個graph表示誰打敗誰的數組 要你列出 哪些人一場沒輸過 哪些人只輸一場
判斷入度為0出度不為0, 入度為一的有哪些
*/
