/*
3171. Find Subarray With Bitwise AND Closest to K
3171. Find Subarray With Bitwise OR Closest to K

*/ 


// 方法1 : TC:O(n*log(U)) SC:O(1)
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            res = min(res, abs(k-nums[i]));
            for(int j = i-1; j >= 0; j--){
                if((nums[j]&nums[i]) == nums[j]) break;
                nums[j] &= nums[i];

                res = min(res, abs(k-nums[j]));
            }
        }

        return res;
    }
};

// 方法2 : TC:O(n*log(U)) SC:O(log(U))
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        int res = INT_MAX;
        unordered_set<int> set;
        for(int i = 0; i < n; i++){
            set.insert(nums[i]);
            res = min(res, abs(nums[i] - k));
            unordered_set<int> set2;
            for(auto& s : set){
                set2.insert(s&nums[i]);
                res = min(res, abs((s&nums[i])-k));
            }
            set = set2;
        }
        return res;
    }
};

// 題目改名並且換成OR TC:O(n*log(U)) SC:O(log(U))
class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        long long res = INT_MAX;
        set<long long> set, tmp;
        for(int i = 0; i < n; i++){
            res = min(res, (long long)abs(k-nums[i]));
            for(auto &val : set){
                long long cur = val | nums[i];
                tmp.insert(cur);
            }
            tmp.insert(nums[i]);
            auto iter = tmp.upper_bound(k);
            if(iter != tmp.end()){
                res = min(res, abs(k - *iter));
            }
            if(iter != tmp.begin()){
                res = min(res, abs(k - *prev(iter)));
            }
            set = tmp;
            tmp.clear();
        }

        return res;
    }
};

/*
把某個區間數字AND在一起 abs|k - result| minimize 
相同為1 不同為0
這意思是在說 AND結果越貼近k越好
首先先想到AND特性會是越AND越小 所以有個數學技巧大概會是log(U) U = max(nums) 的時間可以知道前面AND的結果
因為一旦往回看AND的時候發現AND的數值與原先相同 就不用繼續往回看了 那麼一個數值最多會被AND幾次-> 2^30 -> 30 次
所以log(U)最大大概就是30
時間複雜度分析要去想每一行會執行幾次 不能看到loop就覺得他是O(n)
這題如果是問GCD 也是變小 道理跟AND相同 因為GCD也是會去減半的也是log複雜度 or可以說omega(n)
也可以加入人為約束 例如LCM 會變大的 當超過2*k就不算了
*/ 
