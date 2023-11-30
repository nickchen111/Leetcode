/*
1340. Jump Game V
*/

// TC:O(d*n) SC:O(n) 
class Solution {
    int memo[1001];
    int d;
public:
    int maxJumps(vector<int>& arr, int d) {
        this->d = d;
        int res = 0;
        for(int i = 0; i<arr.size(); i++){
            DFS(i,arr);
            res = max(res,memo[i]);
        }

        return res;
    }
    int DFS(int i, vector<int>& arr){
        
        if(memo[i] != 0) return memo[i];

        int res = 1;
        for(int k = 1; k<=d; k++){
            if(i+k >= arr.size()) break;
            if(arr[i+k] >= arr[i]) break;
            res = max(res,DFS(i+k,arr)+1);
        }
        for(int k = 1; k<=d; k++){
            if(i-k < 0) break;
            if(arr[i-k] >= arr[i]) break;
            res = max(res, DFS(i-k,arr)+1);
        }

        memo[i] = res;
        return res;
    }
};
