/*
2285. Maximum Total Importance of Roads
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        vector<LL> indegree(n);
        for(auto road : roads){
            int a = road[0], b = road[1];
            indegree[a] ++;
            indegree[b] ++;
        }
        sort(indegree.begin(), indegree.end());
        LL res = 0;
        int count = 1;
        for(auto num : indegree){
            res += num*count;
            count ++;
        }

        return res;
    }
};
