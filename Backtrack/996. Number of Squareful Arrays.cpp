/*
996. Number of Squareful Arrays
*/

// 狀態壓縮DP 遞推 + 遞歸 TC:O(n^2 * 2^n) SC:O(n^2 * 2^n)
class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> dp(1 << n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                dp[1 << i][i] = 1;
            }
        }

        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) continue;

                for (int j = 0; j < n; ++j) {
                    if (j == i || (mask & (1 << j))) continue;

                    int square = sqrt(nums[j] + nums[i]);
                    if (square * square != nums[j] + nums[i]) continue;

                    if (j > 0 && nums[j] == nums[j - 1] && !(mask & (1 << (j - 1)))) continue;

                    dp[mask | (1 << j)][j] += dp[mask][i];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += dp[(1 << n) - 1][i];
        }
        return res;

        // vector<vector<int>> memo((1<<n), vector<int>(n,-1));
        // auto dfs = [&](auto &&dfs, int prev, int status) -> int {
        //     if(status == (1<<n) - 1) return 1;
        //     if(memo[status][prev] != -1) return memo[status][prev];
        //     int ret = 0;
        //     for(int i = 0; i < n; i++) {
        //         if(i && nums[i] == nums[i-1] && ((status >> i) & 1) == 0 && ((status >> (i-1)) & 1) == 0) continue;
        //         if(((status >> i) & 1) == 0) {
        //             int square = sqrt(nums[i] + nums[prev]);
        //             if(square * square == nums[i] + nums[prev]) {
        //                 ret += dfs(dfs, i, status | (1<<i));
        //             }
        //         }
        //     }
        //     return memo[status][prev] = ret;
        // };
        // int res = 0;
        // for(int i = 0; i < n; i++) {
        //     if(i && nums[i] == nums[i-1]) continue;
        //     res += dfs(dfs, i, (1<<i));
        // }
        // return res;
    }
};


// TC:O(2^n) SC:O(2^n) int last 寫法
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

// 另種寫法
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
        for(int i = 0; i<graph[cur].size(); i++){
            if(visited[graph[cur][i]]) continue;
            if(i && visited[graph[cur][i-1]] == 0 && nums[graph[cur][i-1]] == nums[graph[cur][i]]) continue;
            
            visited[graph[cur][i]] = 1;
            DFS(nums,graph[cur][i],count+1);
            visited[graph[cur][i]] = 0;
        }
    }
};
