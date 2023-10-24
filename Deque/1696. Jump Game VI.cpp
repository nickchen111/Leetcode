/*
1696. Jump Game VI
*/


//deque 單調遞減隊列
class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        if(nums.size()==1) return nums[0];
        int n = nums.size();
        deque<pair<int, int>> dq;//紀錄數值跟index
        dq.push_back({nums[0],0});//單調遞減

        for(int i = 1; i<n; i++){
            //首先如果超過區間肯定要刪除
            while(!dq.empty() && i - dq.front().second > k){//區間數量頂多k+1個
                dq.pop_front();
            }

            int curStep = dq.front().first + nums[i];
            while(!dq.empty() && dq.back().first < curStep){
                dq.pop_back();
            }
            
            dq.push_back({curStep, i});

        }

        return dq.back().first;
    }
};

//自頂向下遞迴
class Solution {
    //自頂向下遞迴
public:
    int maxResult(vector<int>& nums, int k) {
        if(nums.size()==1) return nums[0];
        int n = nums.size();

        return dp(nums, n-1,k);
    }
    int dp(vector<int>& nums, int p, int k){//一個計算dp[p]的函式 要走到p的位置最多可以得幾分
        if(p == 0) return nums[0];
        if(p < 0) return INT_MIN;//讓他不可能被選擇到

        int res = INT_MIN;
        //
        for(int i = 1; i<=k; i++){
            res = max(res, dp(nums, p-i, k));
        }
        res+=nums[p];

        return res;
    }
};

//帶備忘錄
class Solution {
    //自頂向下遞迴
public:
    vector<int> memo;
    int maxResult(vector<int>& nums, int k) {
        if(nums.size()==1) return nums[0];
        int n = nums.size();
        memo = vector<int>(n, INT_MIN);

        return dp(nums, n-1,k);
    }
    int dp(vector<int>& nums, int p, int k){//一個計算dp[p]的函式 要走到p的位置最多可以得幾分
        if(p == 0) return nums[0];
        if(p < 0) return INT_MIN;//讓他不可能被選擇到

        if(memo[p] != INT_MIN) return memo[p];

        for(int i = 1; i<=k; i++){
            memo[p] = max(memo[p], dp(nums, p-i, k));
        }
        memo[p]+=nums[p];

        return memo[p];
    }
};

//自底向上迭代
class Solution {
    //向上迭代
public:
    int maxResult(vector<int>& nums, int k) {
        if(nums.size()==1) return nums[0];
        int n = nums.size();
         //跳到某個位置時最大得分是多少 取決於他之前的k個位置最大得分是多少
        vector<int> dp(n,INT_MIN);
        dp[0] = nums[0];
        for(int i = 1; i<n; i++){
            for(int j = 1; j<=k; j++){
                if(i-j < 0) continue;
                dp[i] = max(dp[i], dp[i-j]);
            }
            dp[i]+=nums[i];
        }
        return dp[n-1];
    }
};

/*
解題思路：
dp[i]定義 走到nums[i]最多的分數值
用dp的話會發現
dp[i] 會由 dp [i-k][i-k+1][i-k+2]....[i-1]中選一個最大的然後加上nums[i]
但是這樣在進行過程中會有許多次重複計算 sense到每次都是走一格少一格-> slide window maximum
用deque去做 (設計or 不設計struct皆可)
tc: O(n)

此題可以從暴力遞迴 -> 帶備忘錄-> 自底向上迭代->deque單調遞減隊列
*/
