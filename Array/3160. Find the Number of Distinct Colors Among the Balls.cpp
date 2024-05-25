/*
3160. Find the Number of Distinct Colors Among the Balls
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> ball2color; // 某個球是否被染色過了
        unordered_map<int, int> color2freq; // 染了什麼顏色 以及他被染色的次數
        
        int n = queries.size();
        vector<int> res(n);
        for(int i = 0; i < n; i++){
            int ball = queries[i][0], color = queries[i][1];
            if(ball2color.find(ball) != ball2color.end()){
                color2freq[ball2color[ball]] -= 1;
                if(color2freq[ball2color[ball]] == 0){
                    color2freq.erase(ball2color[ball]);
                }
            }
            ball2color[ball] = color;
            color2freq[color] += 1;
            res[i] = (int)color2freq.size();
        }
        
        return res;
    }
};
