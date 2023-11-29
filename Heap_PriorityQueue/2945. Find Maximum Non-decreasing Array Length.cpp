/*
2945. Find Maximum Non-decreasing Array Length
*/

// 線性解  TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int findMaximumLength(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(),0);
        vector<LL> dp(n+1);
        vector<int> len(n+1);
        vector<LL> presum(n+1);
        for(int i =1; i<=n; i++){
            presum[i] = presum[i-1]+nums[i];
        }

        map<LL,int> map;//presum+dp->idx
        map[0] = 0;//presum+dp 為0 在index 0的位置
        for(int i = 1; i<=n; i++){
            auto iter = map.upper_bound(presum[i]);
            int j = prev(iter)->second;
            len[i] = len[j]+1;
            dp[i] = presum[i]-presum[j];
            
            
            
            while(!map.empty() && map.rbegin()->first >= presum[i]+dp[i]){
                map.erase(--map.end());
            }
            map[presum[i]+dp[i]] = i;
        }
        

        return len[n];
    }
};


// N^2解
class Solution {
public:
    int findMaximumLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1,0);
        vector<int> len(n+1,0);

        for(int i = 1; i<=n; i++){
            int sum = nums[i-1];
            int j = i-1;
            while(j >=0 && sum < dp[j]){
                sum += nums[j];
                j--;
            }

            dp[i] = sum;
            len[i] = len[j] + 1;
        }

        return len[n];
    }
};


/*
此題想讓一個序列變單調遞增 過程如果遇到遞減就要讓他跟旁邊的數字瘋狂合併 直到可以繼續遞增為止 試問要變成單調遞增最長可以維持的數組長度為多少
nums: x x x  [ x x x ] [x x x ]
                dp[j].  dp[i]
len: if(dp[i]>=dp[j]) len[i] = len[j]+1
we want to find largest s.t. dp[i]>=dp[j]; 也就是j盡量往後
dp[i]:some subarray sum enjding at i

dp[i]>=dp[j]
想看有沒有更快方法找出之前的越後面越好的dp[j]
轉成presum形式 presum[i]-presum[j] >= dp[j]
presum[j]+dp[j] <= presum[i] ->i要快速找到p小於等於他的j的位置->upper_bound
presum[j]+dp[j]將此資訊存起來->map 
看到這裡會發現其實我們也是要維護一個遞增heap key:presum+dp val->index 會希望index盡量大 但是key要小
所以插入一個key進去之後有比他大的key值 他們的index都是比較小的 那麼他們都可以踢掉
*/
