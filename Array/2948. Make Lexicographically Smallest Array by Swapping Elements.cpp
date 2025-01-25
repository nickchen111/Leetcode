/*
2948. Make Lexicographically Smallest Array by Swapping Elements
*/

// 2025.01.25
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> arr(n);
        iota(arr.begin(), arr.end(), 0);
        ranges::sort(arr, [&](int i, int j){return nums[i] < nums[j];});
        vector<int> res(n);
        int i = 0;
        while(i < n) {
            int st = i;
            i += 1;
            while(i < n && nums[arr[i]] - nums[arr[i-1]] <= limit) {
                i += 1;
            }
            vector<int> idx(arr.begin() + st, arr.begin() + i);
            ranges::sort(idx);
            for(int j = 0; j < idx.size(); j++) {
                res[idx[j]] = nums[arr[st++]];
            }
        }
        return res;
    }
};

// Union find
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> pa(n);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(pa[x] != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x, int y) {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x;
            else pa[x] = y; 
        };
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++) {
            arr.emplace_back(nums[i], i);
        }
        ranges::sort(arr);
        // 滑窗merge
        int i = 0;
        for(int j = 0; j < n; j++) {
            while(arr[j].first - arr[i].first > limit) i += 1;
            merge(arr[j].second, arr[i].second);
        }
        unordered_map<int, vector<int>> mp; // pa => number
        for(int i = 0; i < n; i++) mp[find(i)].emplace_back(nums[i]);
        for(auto &p : mp) ranges::sort(p.second.begin(), p.second.end());
        vector<int> res(n);
        vector<int> idx(n);
        for(int i = 0; i < n; i++) {
            int idxx = find(i);
            res[i] = mp[idxx][idx[idxx]++];
        }
        return res;
    }
};

/*
可以交換元素 只要abs(nums[i] - nums[j]) <= limit
*/

// TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            arr.push_back({nums[i],i});
        }

        sort(arr.begin(), arr.end());
        vector<vector<pair<int,int>>> helper = {{arr[0]}};
        for(int i = 1; i < n; i++){
            if(arr[i].first - arr[i-1].first <= limit){
                helper.back().push_back(arr[i]);
            }
            else helper.push_back({arr[i]});
        }

        for(const auto &t : helper){
            vector<int> idx;
            //將 有可能交換的index取出
            for(auto &p : t){
                idx.push_back(p.second);
            }
            sort(idx.begin(), idx.end());
            for(int i = 0; i < idx.size(); i++){
                nums[idx[i]] = t[i].first;
            }
        }
        
        return nums;
    }
};

/*
此題說要求字母序最小的排列方式 但是如果想將兩個數字換位置他們必須相減小於limit
[1,7,6,18,2,1] [1,6,7,18,1,2]
[1 1 2 6 7 18]
這題的解法是先將所有數字紀錄他的數值跟index 然後按照數值做由小到大的排序
之後再開始將可以換位置的數字湊成一組 最佳解的狀況是在答案數組內這些數字的順序要是對的
類似index sorting的思想
*/
