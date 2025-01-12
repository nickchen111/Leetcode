// TC:O(n * sqrt(mx) * ⍺(n)) SC:O(n)
class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> pa(n);
        vector<int> factor(mx+1, -1);
        iota(pa.begin(), pa.end(), 0);
        vector<int> size(n,1);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) {
                size[x] += size[y];
                pa[y] = x;
            }
            else if(x > y) {
                size[y] += size[x];
                pa[x] = y;
            }
        };

        for(int i = 0; i < n; i++) {
            int curNum = nums[i];
            for(int j = 2; j*j <= curNum; j++) {
                if(curNum % j == 0) {
                    if(factor[j] == -1) factor[j] = i;
                    else {
                        merge(factor[j], i);
                    }
                    while(curNum % j == 0) curNum /= j;
                }
            }
            if(curNum > 1) {
                if(factor[curNum] == -1) factor[curNum] = i;
                else {
                    merge(factor[curNum], i);
                }
            }
        }
        // unordered_set<int> set;
        // for(int i = 0; i < n; i++) {
        //     set.insert(find(i));
        // }
        int res = 0;
        for(int i = 0; i < n; i++) res = max(res, size[i]);
        return res;
    }
};
