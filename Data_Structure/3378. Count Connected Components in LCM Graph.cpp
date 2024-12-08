/*
3378. Count Connected Components in LCM Graph
*/

// TC: O(n + lgM * tlgt) M 為union的數值 SC:O(n)
class Solution {
    
public:
    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(parent[rt] != rt) {
                rt = parent[rt];
            }
            
            while(parent[x] != rt) {
                int tmp = parent[x];
                parent[x] = rt;
                // x = tmp;
            }
            return rt;
        };
        vector<int> idx(threshold+1, -1); // -1 代表沒有這個數字
        for(int i = 0; i < n; i++) {
            if(nums[i] <= threshold) {
                idx[nums[i]] = i;
            }
        }
        // lcm = x*y / gcd(x,y) <= threshold gcd在分母 枚舉他可以做調和級數
        for(int g = 1; g <= threshold; g++) {
            int min_x = -1;
            for(int x = g; x <= threshold; x += g) {
                if(idx[x] != -1) {
                    min_x = x;
                    break;
                }
            } 
            if(min_x == -1) continue;
            int fa = find(idx[min_x]);
            int upper = (long long) g * threshold / min_x;
            for(int y = min_x + g; y <= upper; y += g) {
                if(idx[y] >= 0) {
                    int fj = find(idx[y]);
                    if(fj != fa) {
                        parent[fj] = fa;
                        n--; // 聯通塊個數減一
                    }
                }
            }
        }
        
        return n;
    }
};
