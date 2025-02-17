// TC:O(n + m + k + klgk) n,m 為原數組長度, k 為過濾後數組長度 SC:O(m + k)
class Solution {
public:
    int minOperations(vector<int>& target, vector<int>& arr) {
        // 剛開始看會覺得是LCS 看了提示才想到可以將獨特元素轉index 然後換到另一個數組 去找LIS... 這題難點就在這 所以LCS跟LIS原來有這麼酷的性質
        int m = target.size(), n = arr.size();
        vector<int> nums;
        unordered_map<int,int> mp;
        for(int i = 0; i < m; i++) mp[target[i]] = i;
        for(int i = 0; i < n; i++) {
            if(mp.count(arr[i])) {
                nums.emplace_back(mp[arr[i]]);
            }
        }
        int ng = 0;
        n = nums.size();
        for(int i = 0; i < n; i++) {
            int j = lower_bound(nums.begin(), nums.begin() + ng, nums[i]) - nums.begin();
            if(j == ng) {
                nums[ng] = nums[i];
                ng += 1;
            }
            else {
                nums[j] = nums[i];
            }
        }
        return m - ng;
    }
};

/*
獨特元素 []
可重複元素 [] 
想讓獨特元素會是可重複元素列也有該subsequence 
最少需要操作多少次?
*/
