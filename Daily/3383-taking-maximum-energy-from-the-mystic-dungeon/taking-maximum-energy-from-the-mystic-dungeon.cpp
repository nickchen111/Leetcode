class Solution {
    int dp[100005];
    int res = INT_MIN/2;
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();
        
        for(int i = 0; i < n; i++){
            dp[i] = INT_MIN/2;
        }
        
        for(int i = 0; i < n; i++){
            if(dp[i] != INT_MIN/2) continue;
            DFS(energy,i,k);
        }
        
        return res;
    }
    int DFS(vector<int>& energy,int x, int k){
        int n = energy.size();
        if(x >= n) return 0;
        if(dp[x] != INT_MIN/2) return dp[x];
        int cur = DFS(energy, x + k, k);
        dp[x] = cur + energy[x];
        
        res = max(res, dp[x]);
        
        return dp[x];
    }
};