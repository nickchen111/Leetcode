/*
3276. Select Cells in Grid With Maximum Score
*/

// 2025.01.01 
class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        unordered_map<int, vector<int>> pos;
        int maxVal = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                maxVal = max(maxVal, grid[i][j]);
                if(pos[grid[i][j]].empty() || pos[grid[i][j]].back() != i) pos[grid[i][j]].push_back(i);
            }
        }

        vector<vector<int>> memo(maxVal+1, vector<int>(1 << m, -1));
        auto dfs = [&](auto &&dfs, int j, int mask) -> int {
            if(j == 0) return 0;
            if(mask == (1 << m) - 1) return 0;
            if(memo[j][mask] != -1) return memo[j][mask];
            int ret = dfs(dfs, j-1, mask);
            for(int p : pos[j]) {
                if(((mask >> p) & 1) == 0)
                    ret = max(ret, dfs(dfs, j-1, mask | (1 << p)) + j);
            }

            return memo[j][mask] = ret;
        };

        return dfs(dfs, maxVal, 0);
    }
};

// TC:O(mn*2^m) mn = 出現的數字種類數量 SC:O(2^m)
class Solution {
    vector<vector<int>> grid;
    int m, n;
    vector<vector<int>> memo;
    unordered_map<int, vector<int>> pos;
    vector<int> all_nums;
    int maxVal = 0;
public:
    int maxScore(vector<vector<int>>& grid) {
        m = grid.size();

        this -> grid = grid;
        for(int i = 0; i < m; i++){
            for(int x : grid[i]){
                pos[x].push_back(i);
                maxVal = max(maxVal, x);
            }
        }
    
        memo.resize(maxVal+1, vector<int>(1<<m, -1)); // 選到某個數字之後 目前選了哪幾個row

        return DFS(maxVal, 0);
        
    }
    int DFS(int i, int j){
        if(i == 0) return 0;

        if(memo[i][j] != -1) return memo[i][j];
        int res = DFS(i-1, j);
        
        for(auto & k : pos[i]){
            if(((j>>k) & 1) == 0){
                res = max(res, DFS(i-1, j | 1 << k) + i);
            }
        } 

        return memo[i][j] = res;
        
    }
};


// my solution 
class Solution {
    vector<vector<int>> grid;
    int m, n;
    int res = 0;
    vector<int> arr;
public:
    int maxScore(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        for(int i = 0; i < m; i++){
            sort(grid[i].rbegin(), grid[i].rend());
        }
        
        this -> grid = grid;
        arr.resize(101);
        for(int j = 0; j < n; j++){
            arr[grid[0][j]] = 1;
            helper(1, grid[0][j]);
            arr[grid[0][j]] = 0;
        }
       
        return res;
        
    }
    void helper(int row, int sum){
        if(row == m){
            res = max(res, sum);
            return;
        }
        
        // memo 就是後面剩多少個!? left 0 直接當前可以的最大 還剩下一個 就要選到兩個 -> 0 : 1 1 : 2
        int count = 0;
        bool flag = 0;
        
        for(int j = 0; j < n; j++){
            if (arr[grid[row][j]] == 1) continue;
            flag = 1;
            arr[grid[row][j]] = 1;
            helper(row+1, sum + grid[row][j]);
            arr[grid[row][j]] = 0;
            count += 1;
            if(count == m - row) break;
        }
        
        if(flag == 0){
            helper(row+1, sum);
        }
        
    }
};

/*
不能選同一個row
選擇路徑中 不能有重複的 問說總和最大多少
m = n = 10
10^10
走到某row 已經選擇了哪些數字的最大總和是
dp[i][j] 他肯定會有個路徑 某數字連接到前面某位置
可以 n^3

100 * 10 看目前選了? 
肯定有很棒的memo 可以停損
每行其實是紀錄最大的9*8*7*6...
每一行其實可選可不選 但大概率都會選
後面的row 如果沒有重複 那肯定可以選最大的數字 但如果有 就要選次大 -> sort 
[[16,60,16,60,60,60,60,67,32,15],[30,76,4,60,91,67,32,55,56,97],[100,76,60,100,55,30,82,44,87,100],[76,11,56,78,31,56,56,4,55,60],[1,30,27,54,92,53,76,23,55,77],[55,100,28,54,26,26,93,26,78,100],[23,55,25,4,16,8,37,95,60,71],[30,2,36,62,1,100,92,59,16,97],[16,30,87,4,77,15,60,97,28,30],[4,32,55,68,79,33,4,60,10,73]]
*/
