/*
1791. Find Center of Star Graph
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> indegree(n+2,0);
        for(auto edge : edges){
            int a = edge[0], b = edge[1];
            indegree[b] += 1;
            indegree[a] += 1;
            if(indegree[a] == n) return a;
            if(indegree[b] == n) return b;
        }

        return -1;
    }
};
