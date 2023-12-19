/*
2033. Minimum Operations to Make a Uni-Value Grid
*/

// Mediaun Thoery + Sort  + Remainder TC:O(ngln + n) SC:O(n)
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();
        int mod = grid[0][0]%x;

        vector<int> arr;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] % x != mod) return -1;
                arr.push_back(grid[i][j] / x );
            }
        }

        sort(arr.begin(), arr.end());
        int mid = arr.size()/2;
        int res = 0;
        for(int i = 0; i < arr.size(); i++){
            res += abs(arr[i] - arr[mid]);
        }

        return res;
    }
};

//Presum + Sort TC:O(ngln + n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size();
        int n = grid[0].size();
        vector<LL> arr;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                arr.push_back(grid[i][j]);
            }
        }
        
        int sz = arr.size();
        sort(arr.begin(), arr.end());
        vector<LL> presum(sz+1);
        presum[0] = 0;
        for(int i = 1; i <=sz; i++){
            presum[i] = presum[i-1] + arr[i-1];
        }

        LL res = INT_MAX;
        for(int i = 0; i < sz; i++){
            if(i){
                if((arr[i] - arr[i-1]) % x != 0) return -1;
            }
            LL cost = arr[i]*i - presum[i] + (presum[sz] - presum[i+1]) - (sz-i-1)*arr[i];
            cout << cost;
            if(cost % x == 0) res = min(res, (LL)cost/x);
        }

        return res == INT_MAX ? -1:res;

    }
};

/*
跟週賽2968題很像 但是多了要確認是否可行 
cost = arr[i]*(i) - (presum[i]) + presum[sz] - (sz-i-1)*arr[i];
if(cost % x == 0) res = min(res, cost/x); 
另外一種方法直接用中位數定理 並且藉由餘數就可以知道是否可行 如果要可行 大家餘數都要相同
x x x O x x x
*/
