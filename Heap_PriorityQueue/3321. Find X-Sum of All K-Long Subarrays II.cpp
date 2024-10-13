/*
3321. Find X-Sum of All K-Long Subarrays II
*/


// 我的寫法 較長 TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
    set<pair<LL,LL>> minHeap;
    set<pair<LL,LL>> maxHeap; // 小到大
    map<LL, LL> map;
    int x;
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        this -> x = x;
        vector<LL> res(n-k+1);
        
        for(int i = 0; i < k; i++){
            map[nums[i]] += 1;
        }
        
        LL sum = 0;
        vector<pair<LL,LL>> arr;
        for(auto &p : map) {
            arr.push_back({p.second, p.first}); // freq, val
        }
        sort(arr.begin(), arr.end());

        if(x >= arr.size()) {
            for(int i = 0; i < arr.size(); i++) {
                maxHeap.insert({arr[i].first, arr[i].second});
                sum += arr[i].first*arr[i].second;
            }
        }
        else {
            int count = 0; // map.size() - x 個
            for(int i = 0; i < arr.size(); i++) {
                if(count < (int)arr.size() - x) {
                    minHeap.insert({arr[i].first, arr[i].second});
                    count += 1;
                }
                else {
                    maxHeap.insert({arr[i].first, arr[i].second});
                    sum += arr[i].first*arr[i].second;
                }
            }
        }
        int j = k;
        int i = 0;
        int idx = 1;
        res[0] = sum;

        while(j < n) {
            sum = addOne(nums[j],sum);
            sum = removeOne(nums[i], sum);
            res[idx] = sum;
            i++;
            j++;
            idx++;
        }

        return res;
    }
    LL addOne(LL num, LL sum) {
        LL res = sum;
        map[num] += 1;
        if(maxHeap.size() < x) {
            if(maxHeap.find({map[num]-1, num}) != maxHeap.end()) {
                maxHeap.erase({map[num]-1, num});
                maxHeap.insert({map[num], num});
                res += num;
            }
            else {
                maxHeap.insert({map[num], num});
                res += num;
            }
        }
        else if(maxHeap.size() == x && maxHeap.find({map[num]-1, num}) != maxHeap.end()) {
            maxHeap.erase({map[num]-1, num});
            maxHeap.insert({map[num], num});
            res += num;
        }
        else if(minHeap.size() > 0 && minHeap.find({map[num]-1, num}) != minHeap.end()) {
            minHeap.erase({map[num]-1, num});
            minHeap.insert({map[num], num});
            if(minHeap.rbegin()->first > maxHeap.begin()->first || (minHeap.rbegin()->first == maxHeap.begin()->first && minHeap.rbegin()->second > maxHeap.begin()->second)) {
                res -= (maxHeap.begin()->first * maxHeap.begin()->second);
                res += (minHeap.rbegin()->first * minHeap.rbegin()->second);
                maxHeap.insert({minHeap.rbegin()->first, minHeap.rbegin()->second});
                minHeap.erase({minHeap.rbegin()->first, minHeap.rbegin()->second});
                minHeap.insert({maxHeap.begin()->first, maxHeap.begin()->second});
                maxHeap.erase({maxHeap.begin()->first, maxHeap.begin()->second});
            }
        }
        else {
            if(map[num] > maxHeap.begin()->first || (map[num] == maxHeap.begin()->first && num > maxHeap.begin()->second)) {
                res += map[num]*num;
                res -= maxHeap.begin()->first *  maxHeap.begin()->second;
                minHeap.insert({ maxHeap.begin()->first, maxHeap.begin()->second});
                maxHeap.erase({maxHeap.begin()->first, maxHeap.begin()->second});
                maxHeap.insert({map[num], num});
            }
            else {
                minHeap.insert({map[num], num});
            }
        }

        return res;
    }
    LL removeOne(LL num, LL sum) {
        LL res = sum;
        map[num] -= 1;
        if(maxHeap.find({map[num]+1, num}) != maxHeap.end()) {
            maxHeap.erase({map[num]+1, num});
            maxHeap.insert({map[num], num});
            res -= num;
            if(map[num] == 0) {
                maxHeap.erase({map[num], num});
                if(minHeap.size() > 0) {
                    res += (minHeap.rbegin()->first * minHeap.rbegin()->second);
                    maxHeap.insert({minHeap.rbegin()->first, minHeap.rbegin()->second});
                    minHeap.erase({minHeap.rbegin()->first, minHeap.rbegin()->second});
                }
            }
            else if(minHeap.size() > 0 && (minHeap.rbegin()->first > maxHeap.begin()->first || minHeap.rbegin()->first == maxHeap.begin()->first && minHeap.rbegin()->second > maxHeap.begin()->second)) {
                res -= (maxHeap.begin()->first * maxHeap.begin()->second);
                res += (minHeap.rbegin()->first * minHeap.rbegin()->second);
                maxHeap.insert({minHeap.rbegin()->first, minHeap.rbegin()->second});
                minHeap.erase({minHeap.rbegin()->first, minHeap.rbegin()->second});
                minHeap.insert({maxHeap.begin()->first, maxHeap.begin()->second});
                maxHeap.erase({maxHeap.begin()->first, maxHeap.begin()->second});
            }
        }
        else {
            minHeap.erase({map[num]+1, num});
            if(map[num] > 0)
                minHeap.insert({map[num], num});
        }

        return res;
    }
};

// 較簡潔寫法 
class Solution {
public:
    vector<long long> findXSum(const vector<int>& nums, int k, int x) {
        using pii = pair<int, int>; // 出现次数，元素值
        set<pii> L, R;
        long long sum_l = 0; // L 的元素和
        unordered_map<int, int> cnt;
        auto add = [&](int x) {
            pii p = {cnt[x], x};
            if (p.first == 0) {
                return;
            }
            if (!L.empty() && p > *L.begin()) { // p 比 L 中最小的还大
                sum_l += (long long) p.first * p.second;
                L.insert(p);
            } else {
                R.insert(p);
            }
        };
        auto del = [&](int x) {
            pii p = {cnt[x], x};
            if (p.first == 0) {
                return;
            }
            auto it = L.find(p);
            if (it != L.end()) {
                sum_l -= (long long) p.first * p.second;
                L.erase(it);
            } else {
                R.erase(p);
            }
        };
        auto l2r = [&]() {
            pii p = *L.begin();
            sum_l -= (long long) p.first * p.second;
            L.erase(p);
            R.insert(p);
        };
        auto r2l = [&]() {
            pii p = *R.rbegin();
            sum_l += (long long) p.first * p.second;
            R.erase(p);
            L.insert(p);
        };

        vector<long long> ans(nums.size() - k + 1);
        for (int r = 0; r < nums.size(); r++) {
            // 添加 in
            int in = nums[r];
            del(in);
            cnt[in]++;
            add(in);

            int l = r + 1 - k;
            if (l < 0) {
                continue;
            }

            // 维护大小
            while (!R.empty() && L.size() < x) {
                r2l();
            }
            while (L.size() > x) {
                l2r();
            }
            ans[l] = sum_l;

            // 移除 out
            int out = nums[l];
            del(out);
            cnt[out]--;
            add(out);
        }
        return ans;
    }
};

/*
計算頻率最高的x個 在一定的範圍內滑動 
slide window 但是頻率就會變動

也就是維護前x個頻率高的
先想成每個元素頻率一樣，就是維護最大的前x個
想清楚怎麼添加與刪除一個數 這題就解了
變成維護pair 搭配map 去紀錄
*/
