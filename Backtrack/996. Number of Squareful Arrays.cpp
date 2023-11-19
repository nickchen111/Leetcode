/*
996. Number of Squareful Arrays
*/

// TC:O(2^n) SC:O(2^n)
class Solution {
    int n;
    vector<vector<int>> graph;
    int res = 0;
    bool visited[12];
public:
    int numSquarefulPerms(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        n = nums.size();
        graph.resize(n);

        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                if(i == j) continue;
                if(sqrt(nums[i]+nums[j]) == (int)sqrt(nums[i]+nums[j])){
                    graph[i].push_back(j);
                }
            }
        }
        for(int i = 0; i<n; i++){
            if(i > 0 && nums[i] == nums[i-1]) continue;
            visited[i] = 1;
            DFS(nums,i,1);
            visited[i] = 0;
        }

        return res;
    }
    void DFS(vector<int>& nums,int cur, int count){
        if(count == n){
            res+=1;
            return;
        }
        
        int last = -1;
        for(int i:graph[cur]){
            if(visited[i] == 1) continue;
            if(nums[i] == last) continue;
            last = nums[i];
            visited[i] = 1;
            DFS(nums,i,count+1);
            visited[i] = 0;
        }
    }
};
