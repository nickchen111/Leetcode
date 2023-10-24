/*
1425. Constrained Subsequence Sum
*/


//iterative 是否可優化 如果nums很大會TLE tc:O(n*k)
//次優解 用有序容器 ex: multiset去排序 tc: O(n*lgk)
//最優解 用slide window max deque tc: O(n)
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size(); 
        if(n == 1) return nums[0];

        vector<int> dp(n, INT_MIN);
        dp[0] = nums[0];
        for(int i = 1; i<n; i++){
            for(int j = 1; j<=k; j++){
                if(i-j < 0) continue;
                dp[i] = max(dp[i], max(nums[i], dp[i-j]+nums[i]));
            }
        }

        int res = INT_MIN;
        for(int i = 0; i < n; i++){
            res = max(res, dp[i]);
        }

        return res;
    }
};

//次優解 + multiset tc: O(nlgn) sc:O(2n)
class Solution {
    multiset<int> Set;
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size(); 
        if(n == 1) return nums[0];

        vector<int> dp(n, 0);
        
        for(int i = 0; i<n; i++){
            dp[i] = nums[i];
            if(Set.size() > k && i-k-1 >=0){
                Set.erase(Set.find(dp[i-k-1]));
            }

            if(Set.size() > 0)
                dp[i] = max(dp[i], *Set.rbegin() + nums[i]);

            Set.insert(dp[i]);
        }

        int res = INT_MIN;
        for(int i = 0; i < n; i++){
            res = max(res, dp[i]);
        }

        return res;
    }
};

//最優解 + slide window tc: O(n)  sc: O(n+k)

class Solution {
    deque<int> dq;//存的事index
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size(); 
        if(n == 1) return nums[0];

        vector<int> dp(n, 0);
        int res = nums[0];
        for(int i = 0; i<n; i++){

            while(!dq.empty() &&  dq.front() < i-k) dq.pop_front();//確認是否超載
            dp[i] = nums[i];
            if(dq.size() > 0)  dp[i]= max(dp[i], dp[dq.front()] + nums[i]); //不斷紀錄dp中最大的結果

            while(!dq.empty() && dp[i] > dp[dq.back()]){
                dq.pop_back();
            }

            dq.push_back(i);
            res = max(res, dp[i]);
        }

        return res;
    }
};

/*
dp呢 dp[i] 就是the maximum sum of a non-empty subsequence of nums[i]到這
dp[i] = max (nums[i], dp[i-1] [i-2]... [i-k]+nums[i])取最大的


deque: 
1. check是否nums[i] 大於 dq.back() 是的話就pop
2. check 是否超過數目 是的話 就pop_front()
*/



//recursion+memo 也需要優化
class Solution {
    vector<int> memo;
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size(); 
        if(n == 1) return nums[0];
    
        memo = vector<int>(n, INT_MIN);

        vector<int> dp(n, INT_MIN);
        backtrack(nums, dp, n-1, k);  
        dp[0] = nums[0]; 

        int res= INT_MIN;
        for(int i = 0; i<n; i++){
            res = max(res, dp[i]);
        } 

        return res;
    }

    int backtrack(vector<int>& nums,vector<int>& dp, int cur, int k){
        if(cur == 0) return nums[0];
        

        if(memo[cur] != INT_MIN) return memo[cur];

        for(int i =1; i<=k; i++){
            if(cur-i < 0) continue;
            dp[cur] = max(dp[cur], max(nums[cur], backtrack(nums, dp, cur-i, k)+nums[cur]));
        }

        memo[cur] = dp[cur];

        return dp[cur];
    }
};

