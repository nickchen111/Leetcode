/*
997. Find the Town Judge
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        //找出出度為0的點
        vector<int> outdegree(n+1,0);
        vector<int> indegree(n+1,0);
        for(auto t : trust){
            int a = t[0], b = t[1];
            outdegree[a] += 1;
            indegree[b] += 1;
        }

        int res = -1;
        for(int i = 1; i <= n; i++){
            if(outdegree[i] == 0 && indegree[i] == n-1){
                res = i;
                break;
            }
        }

        return res;
    }
};
