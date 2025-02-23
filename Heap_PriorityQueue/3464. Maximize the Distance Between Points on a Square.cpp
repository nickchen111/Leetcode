// TC:O(nlgn) SC:O(k)
class Solution {
    using LL = long long;
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
        if(k == 0) return 0;
        int m = grid.size(), n = grid[0].size();
        //就是取前面k大的
        priority_queue<int, vector<int>, greater<int>> pq;
        LL ans = 0;
        for(int i = 0; i < m; i++) {
            sort(grid[i].rbegin(), grid[i].rend());
            for(int j = 0; j < min(n, limits[i]); j++) {
                if(pq.size() == k and grid[i][j] <= pq.top()) break;
                pq.push(grid[i][j]);
                ans += (LL)grid[i][j];
                if(pq.size() > k) {
                    ans -= pq.top();
                    pq.pop();
                }
            }
        }
        
        return ans;
        
    }
};
