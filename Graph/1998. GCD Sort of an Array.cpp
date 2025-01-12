// TC:O(nlgn + n * ⍺(n)) SC:O(n)
class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        // gcd > 1
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> pa(n);
        iota(pa.begin(), pa.end(), 0);
        // 4, 10 -> 2
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x; 
            else pa[x] = y;
        };
        vector<int> idx(mx+1, -1);
        for(int i = 0; i < n; i ++) {
            int curNum = nums[i];
            for(int j = 2; j * j <= curNum; j++) {
                if(j > curNum) break;
                if(curNum % j == 0) {
                    if(idx[j] == -1) {
                        idx[j] = i;
                    }
                    else {
                        merge(idx[j],i);
                    }
                    while(curNum % j == 0) curNum /= j;
                }
            }
            if(curNum > 1) {
                if(idx[curNum] == -1) idx[curNum] = i;
                else merge(idx[curNum], i);
            }
        }

        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++) {
            int j = i;
            int mn = INT_MAX;
            int mx = INT_MIN;
            while(j < n && find(i) == find(j)) {
                mn = min(mn, nums[i]);
                mx = max(mx, nums[i]);
                j++;
            }
            arr.push_back({mn, mx});
            i = j - 1;
        }
        
        unordered_map<int, vector<int>> map;
        unordered_map<int, int> pointer;
        for(int i = 0; i < n; i++) {
            map[find(i)].push_back(nums[i]);
            pointer[find(i)] = 0;
        }
        for(auto &[p1, p2] : map) sort(p2.begin(), p2.end());

        vector<int> tmp = nums;
        for(int i = 0; i < n; i++) {
            int paa = find(i);
            tmp[i] = map[paa][pointer[paa]++];
        }
        // for(int i = 1; i < n; i++) {
        //     if(tmp[i] < tmp[i-1]) return false;
        // }
        return is_sorted(tmp.begin(), tmp.end());
    }
};
