/*
3347. Maximum Frequency of an Element After Performing Operations II
*/


// Slide Window TC:O(nlgn + n) SC:O(1)
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        int left = 0, right = 0, cnt = 0;
        // 三指針 判斷
        for(int i = 0; i < n; i++) {
            cnt ++;
            if(i+1 < n && nums[i] == nums[i+1]) continue;

            while(nums[left] < nums[i]-k) {
                left++;
            }

            while(right < n && nums[i] + k >= nums[right]) {
                right++;
            }
            res = max(res, cnt + min(numOperations, right - left - cnt));
            cnt = 0;
        }

        
        int i = 0;
        for(int j = 0; j < n; j++) {
            int x = nums[j];
            while(nums[i] < x - 2*k) {
                i++;
            }

            res = max(res, min(numOperations, j-i+1));
        }

        return res;
    }
};

// 差分 TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> cnt;
        map<int, int> diff;
        for (int x : nums) {
            cnt[x]++;
            diff[x]; // 把 x 插入 diff，以保证下面能遍历到 x
            diff[x - k]++; // 把 [x-k, x+k] 中的每个整数的出现次数都加一
            diff[x + k + 1]--;
        }

        int ans = 0, sum_d = 0;
        for (auto& [x, d] : diff) {
            sum_d += d;
            ans = max(ans, min(sum_d, cnt[x] + numOperations));
        }
        return ans;
    }
};

// 二分 + 差分概念的Hash Set TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();
        unordered_set<int> set;
        sort(nums.begin(), nums.end());
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++) {
            set.insert(nums[i]), set.insert(nums[i]-k), set.insert(nums[i]+k);
            map[nums[i]] += 1;
        }
        int res = 0;
        for(auto & num : set) {
            int tmp = 0;
            // 從 比x大到x+k有多少個
            tmp += upper_bound(nums.begin(), nums.end(), num + k) - upper_bound(nums.begin(), nums.end(), num);
            // 跟x-k一樣到x之前有多少個
            tmp += lower_bound(nums.begin(), nums.end(), num) - lower_bound(nums.begin(), nums.end(), num - k);
            
            tmp = min(tmp, numOperations);
            res = max(res, tmp + map[num]);
        }
        
        return res;
    }
};

/*
可以任意加上 -k 到 k的數字 k可以到1e9 
需要操作x次 x 為1e5
並且選過的數字就不能再選了 所以 至少要挑不同的x個去操作
問說最後出現頻率最高的數字是?
0 2 5 8 10 18
0來說 : 2 5 8 10 18
2來說 : 2 3 6 8 16
去計算說都要變某個數字的代價是多少？
前面每個數字可以在合理範圍內變成的 會有一個窗口 x 這段窗口
x x x x x 5 x x x x 
可以計算出前面的數字要變成我所需cost
[42,11,52]
96
1
[2,33]
47
0
*/
