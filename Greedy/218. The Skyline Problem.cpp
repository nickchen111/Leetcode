/*
218. The Skyline Problem
*/


//sweeping line  TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //hash table讓他幫我們按照pos排序
        map<int, vector<pair<int,int>>> map; //pos-> {heights, flag} flag為1代表上升 -1代表下降
        for(auto build:buildings){
            map[build[0]].push_back({build[2], 1});
            map[build[1]].push_back({build[2], -1});
        }

        multiset<int> set;
        vector<vector<int>> res;
        for(auto& [pos, pairs]:map){
            for(auto& [height, flag]:pairs){
                if(flag == 1){
                    set.insert(height);
                }
                else{
                    set.erase(set.find(height));
                }
            }
            int H = set.empty() ? 0:*set.rbegin();
            if(res.empty() || res.back()[1] != H){
                res.push_back({pos,H});
            }
        }
        return res;
    }
};


/*
此題要求在高樓的天際線對應pos 跟高度
sweeping line技巧來解這道題 or Segment tree
*/
