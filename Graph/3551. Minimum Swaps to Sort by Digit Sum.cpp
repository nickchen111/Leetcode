// Union Find TC:O(n * (lgn + α)) SC:O(n)
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<tuple<int,int,int>> arr(n);
        for (int i = 0; i < n; i++) {
            int s = 0;
            for (int x = nums[i]; x > 0; x /= 10) {
                s += x % 10;
            }
            arr[i] = {s, nums[i], i};
        }
        ranges::sort(arr);
        int cnt = n;
        vector<int> pa(n);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](this auto&& find, int x) -> int {
            if (x != pa[x]) pa[x] = find(pa[x]);
            return pa[x];
        };
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if (x < y) {
                pa[y] = x;
                cnt -= 1;
            }
            else if (x > y) {
                pa[x] = y;
                cnt -= 1;
            }
        };
        for (int i = 0; i < n; i++) {
            merge(get<2>(arr[i]), i);
        }
        return n - cnt;
    }
};

// Cycle Detection by DFS TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        auto digitSum = [](int x) {
            int res = 0;
            while (x) {
                res += x % 10;
                x /= 10;
            }
            return res;
        };
        vector<pair<pair<int, int>, int>> val_with_index;
        for (int i = 0; i < n; i++) {
            val_with_index.push_back({{digitSum(nums[i]), nums[i]}, i});
        }
        sort(val_with_index.begin(), val_with_index.end());

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || val_with_index[i].second == i) continue;
            int cycle_size = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = val_with_index[j].second;
                cycle_size++;
            }
            if (cycle_size > 0) swaps += (cycle_size - 1);
        }

        return swaps;
    }
};

// Index Sorting or map 每遇到不同就交換到相同: 一樣意思 只是index sorting 是以當下錯誤的數字要把它換到正確位置，但是換來的不一定正確，而我自己寫的map 是這次肯定換到正確位置 但是後面換過去的位置不一定正確
// TC:O(nlgn) SC:O(n) 但是牽扯到map隨機訪問 效率不如UF or DFS
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        auto digitSum = [](int x) {
            int res = 0;
            while (x) {
                res += x % 10;
                x /= 10;
            }
            return res;
        };
        vector<pair<pair<int, int>, int>> val_with_index;
        unordered_map<int,int> mp;
        for (int i = 0; i < n; i++) {
            // mp[nums[i]] = i
            val_with_index.push_back({{digitSum(nums[i]), nums[i]}, i});
        }
        sort(val_with_index.begin(), val_with_index.end());
        int ans = 0;
        // index Sorting
        for (int i = 0; i < n; i ++) mp[val_with_index[i].first.second] = i;
        for (int i = 0; i < n; i++) {
            while (val_with_index[i].first.second != nums[i]) {
                ans += 1;
                swap(nums[i], nums[mp[nums[i]]]);
            }
        }
        return ans;

        /*
        Map 
        vector<bool> visited(n, false);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (val_with_index[i].first.second != nums[i]) {
                // 找出這兩個數字位置
                int num1 = nums[i], num2 = val_with_index[i].first.second;
                swap(nums[i], nums[mp[num2]]);
                int pos = mp[num2];
                mp[num2] = mp[num1];
                mp[num1] = pos;
                ans += 1;
            }
        }
        */
    }
};
