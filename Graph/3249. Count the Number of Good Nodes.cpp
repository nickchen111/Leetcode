/*
3249. Count the Number of Good Nodes
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<vector<int>> next;
    int res = 0;
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        int n = edges.size();
        next.resize(n+1);
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }
        DFS(0, -1);
        
        return res;
    }
    int DFS(int cur, int pa){
        
        int count = 0;
        int sum = 1;
        bool flag = 1;
        for(auto nxt : next[cur]){
            if(nxt == pa) continue;
            if(count == 0){
                count = DFS(nxt, cur);
                sum += count;
            }
            else {
                int nxtCount = DFS(nxt, cur);
                if(count != nxtCount){
                    flag = 0;
                }
                sum += nxtCount;
            }
        }
        
        if(flag) res += 1;
        
        return sum;
    }
};
