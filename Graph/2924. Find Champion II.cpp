/*
2924. Find Champion II
*/

//TC:O(V+E) SC:O(V) 
class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        //判斷入度
        vector<int> indegree(n,0);
        for(auto edge:edges){
            indegree[edge[1]]+=1;
        }
        
        int count = 0;
        int res = 0;
        for(int i = 0; i < indegree.size(); i++){
            if(indegree[i] == 0){
                count+=1;
                res = i;
            }
            if(count > 1) return -1;
        }
        
        return res;
    }
};
