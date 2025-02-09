// 模板解 TC:O(n*mlg(m,n)) SC:O(n*m)
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        for (int k = 1; k < m + n; k++) {
            
            int min_j = max(n - k, 0); 
            int max_j = min(m + n - 1 - k, n - 1);
            vector<int> a;
            for (int j = min_j; j <= max_j; j++) {
                a.push_back(grid[k + j - n][j]);
            }
            if (min_j > 0) {
                ranges::sort(a);
            } else { 
                ranges::sort(a, greater<int>());
            }
            for (int j = min_j; j <= max_j; j++) {
                grid[k + j - n][j] = a[j - min_j];
            }
        }
        return grid;
    }
};

// 
class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> ans(n, vector<int>(n));
        for(int j = n-1; j >= 1; j--) {
            int startx = 0, starty = j;
            int i0 = 0; int j0 = j;
            vector<int> arr;
            while(j0 < n && i0 < n) {
                arr.push_back(grid[i0][j0]);
                i0 += 1, j0 += 1;
            }
            sort(arr.begin(), arr.end());
            int idx = 0;
            while(startx < n && starty < n) {
                ans[startx][starty] = arr[idx++];
                startx += 1, starty += 1;
            }
        }
        for(int i = 0; i < n; i++) {
            int startx = i, starty = 0;
            int i0 = i; int j0 = 0;
            vector<int> arr;
            while(j0 < n && i0 < n) {
                arr.push_back(grid[i0][j0]);
                i0 += 1, j0 += 1;
            }
            sort(arr.rbegin(), arr.rend());
            int idx = 0;
            while(startx < n && starty < n) {
                ans[startx][starty] = arr[idx++];
                startx += 1, starty += 1;
            }
        }
        return ans;
    }
};
