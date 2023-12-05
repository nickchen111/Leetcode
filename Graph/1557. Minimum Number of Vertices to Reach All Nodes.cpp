/*
1557. Minimum Number of Vertices to Reach All Nodes
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> res;
        vector<int> indegree(n);
        for(const auto &edge:edges){
            indegree[edge[1]]+=1;
        }

        for(int i = 0; i < n; i++){
            if(indegree[i] == 0) res.push_back(i);
        }

        return res;
    }
};

/*
此題無環並且問說最少需要哪些點從這些點出發可以到所有點
找尋入度為零的點
*/
