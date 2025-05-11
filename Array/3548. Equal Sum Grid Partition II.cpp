// TC:O(m * n) SC:O(m * n)
class Solution {
    using ll = long long;
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        ll total = 0;
        vector<ll> rowSum(m, 0), colSum(n, 0);
        unordered_map<int,int> cntTop, cntBot;
        for(int i= 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int v = grid[i][j];
                total += v;
                rowSum[i] += v;
                colSum[j] += v;
                cntBot[v]++;
            }
        }

        auto canRemove = [&](int H, int W, int x,
                             const unordered_map<int,int>& cnt,
                             const vector<pair<int,int>>& endpoints)->bool {
            if(x <= 0) return false;
            if(H >= 2 && W >= 2) {
                auto it = cnt.find(x);
                return it != cnt.end() && it->second > 0;
            }
            for(auto &p : endpoints){
                int i = p.first, j = p.second;
                if(grid[i][j] == x) return true;
            }
            return false;
        };

        // 水平切
        ll sumTop = 0;
        for(int k = 1;k < m; k++){
            for (int j = 0; j < n; j++) {
                int v = grid[k-1][j];
                if (--cntBot[v] == 0) cntBot.erase(v);
                cntTop[v]++;
            }
            sumTop += rowSum[k-1];
            ll sumBot = total - sumTop;
            ll diff = sumTop - sumBot;
            if (diff == 0) return true;
            if (diff > 0) {
                // 從上半部扣 diff
                int H = k, W = n;
                vector<pair<int,int>> ends;
                if (H == 1 && W >= 2) {
                    ends = {{0, 0},{0, n-1}};
                } else if (W == 1 && H >= 2) {
                    ends = {{0, 0},{k-1, 0}};
                }
                if (canRemove(H, W, (int)diff, cntTop, ends))
                    return true;
            } else {
                // 從下半部扣 -diff
                int H = m - k, W = n;
                vector<pair<int,int>> ends;
                if (H == 1 && W >= 2) {
                    ends = {{k, 0},{k, n - 1}};
                } else if (W == 1 && H >= 2) {
                    ends = {{k, 0},{m - 1, 0}};
                }
                if (canRemove(H, W, (int)(-diff), cntBot, ends))
                    return true;
            }
            for(int j = 0; j < n; j++){
                int v = grid[k][j];
                if (--cntBot[v] == 0) cntBot.erase(v);
                cntTop[v]++;
            }
        }

        // 垂直切
        ll sumLeft = 0;
        cntTop.clear();
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                cntBot[ grid[i][j] ]++;

        for(int j = 1; j < n; j++){
            for(int i = 0; i < m; i++){
                int v = grid[i][j-1];
                if (--cntBot[v] == 0) cntBot.erase(v);
                cntTop[v]++;
            }
            sumLeft += colSum[j-1];
            ll sumRight = total - sumLeft;
            ll diff = sumLeft - sumRight;
            if (diff == 0) return true;
            if (diff > 0) {
                // 從左半部扣 diff
                int H = m, W = j;
                vector<pair<int,int>> ends;
                if (H == 1 && W >= 2) {
                    ends = {{0, 0},{0, j - 1}};
                } else if (W == 1 && H >= 2) {
                    ends = {{0, 0},{m - 1, 0}};
                }
                if (canRemove(H,W,(int)diff,cntTop,ends))
                    return true;
            } else {
                // 從右半部扣 -diff
                int H = m, W = n - j;
                vector<pair<int,int>> ends;
                if (H == 1 && W >= 2) {
                    ends = {{0, j},{0, n - 1}};
                } else if(W == 1 && H >= 2) {
                    ends = {{0, j},{m - 1, j}};
                }
                if (canRemove(H, W, (int)(-diff), cntBot, ends))
                    return true;
            }
            for(int i = 0; i < m; i++){
                int v = grid[i][j];
                if (--cntBot[v] == 0) cntBot.erase(v);
                cntTop[v]++;
            }
        }
        return false;
    }
};
