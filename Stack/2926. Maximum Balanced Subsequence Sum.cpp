/*
2926. Maximum Balanced Subsequence Sum
*/

//TC:O(nlgn+n) SC:O(n) 
class Solution {
    using LL = long long;
public:
    long long maxBalancedSubsequenceSum(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n);
        for(int i =0; i<n; i++){
            arr[i] = nums[i]-i;
        }
        //想挑出arr的意義上所有會遞增的子序列 並且求出哪個在nums的意義上總和最大
        map<int, LL> dp;
        LL res = LLONG_MIN;
        for(int i = 0; i<n; i++){
            int x = arr[i];
            //找出大於我的那個值 往前一個就是等於or小於我dp值的
            auto iter = dp.upper_bound(x);
            if(iter != dp.begin()){
                iter = prev(iter);
                dp[x] = max((LL)nums[i],iter->second+nums[i]);
            }
            else{
                dp[x] = nums[i];
            }
            
            res = max(res,dp[x]);

            iter = dp.find(x);
            iter = next(iter);
            while(iter != dp.end() && iter->second <= dp[x]){
                int y = iter->first;
                iter = next(iter);
                dp.erase(y);
            }

        }

        return res;
    }
};

/*
此題從一開始的不等式整理 想到多開一個數組 再由思考子序列怎麼選前面的數值想到DP 但是DP會是n^2解 會超時 如果不用線段樹結合離散化 要想到dp數組的本質就是有序的
map 那如果可以維護一個key value都是單調遞增的棧 那對於後面元素來說都會是最好的選擇 因為key本身代表一定比較小符合題意 value本身如果比較大那就會是更好的人選
意即对于dp里存在 dp[a]=A, dp[b]=B，且a<b, A>=B，那么对于任何一个新元素arr[i]=x，我们如果可以把x接在b后面构造子序列，那么显然不如我们把x接在a后面构成子序列更优。
这样我们就可以把b从dp里弹出去。
nums[ij] - nums[ij-1] >= ij - ij-1
->nums[i]-i >= nums[j]-j  i>=j

i:   0 1 2 3 4 5
nums:x x x x x x 
arr: x x x x x x 

dp[i]:the maximum sum(on nums) when you pick a increasing subsequence from arr and end at i
這個寫法會是n^2
for(int i =0; i<n; i++){
    for(int j = 0; j<i; j++){
        if(arr[j] < arr[i])
            dp[i] = max(dp[i],d[j]+nums[i]);
    }
}
dp[x]:the maximum sum(on nums) when you pick a increasing subsequence from arr and end at x
for(int i = 0; i<n; i++){
    int x=arr[i];
    for(int y:sort(0:i-1) && y<x){
        dp[x] = max(dp[x],dp[y]+nums[i]);
    }
}
如果可以排序他類似單調站的感覺 那麼不就更好找   
所以想到說 排序前面的arr 用個map 去映射他的dp值 會希望dp值跟arr值都是遞增的 
key:arr的值 value->dp值
*/
