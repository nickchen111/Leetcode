/*
410. Split Array Largest Sum
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int left = INT_MAX;
        int right = 0;
        for(int i = 0; i<nums.size(); i++){
            left = min(left, nums[i]);
            right+=nums[i];
        }

        while(left < right){
            int cap = left + (right-left)/2;
            if(checkOk(nums, k, cap)){
                right = cap;
            }
            else{
                left = cap+1;
            }
        }

        return left;
    }

    bool checkOk(vector<int>& nums, int k, int cap){
        int count = 0;
        for(int i =0; i<nums.size(); i++){
            int j = i;
            int sum = 0;
            while(j < nums.size() && sum+nums[j] <= cap){
                sum+=nums[j];
                j++;
            }
            count++;

            if(count > k) return false;
            i = j-1;
        }

        return true;
    }
};
//DP TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        auto dp = vector<vector<long>>(n+1, vector<long>(k+1));
        nums.insert(nums.begin(), 0);

        //base case
        for(int i =1; i<=n; i++){
            dp[i][1] += dp[i-1][1] + nums[i];
        }
        for(int i = 1; i<=n; i++){
            //因為2個數字不可能分三份 三個數字不可能份四份...
            for(int K = 2; K<=min(k,i); K++){
                dp[i][K] = max(dp[i-1][K-1],(long)nums[i]);
                //定義t 為讓 i到t之前可能有好幾派 留一派出來
                for(int j = 1; j<=i-1; j++){
                    long temp = max((j >=K-1) ? dp[j][K-1]:INT_MAX, dp[i][1]-dp[j][1]);// 用dp數組就可以計算前綴和 t+1~i
                    dp[i][K] = min(dp[i][K], temp);
                }
            }
        }

        return dp[n][k];
    }
};

/*
此題跟 1011相同概念
不過這題是subarray 必須是連續的 但殊途同歸 一樣用貪心法一個一個裝進去 必定會得到解

dp解法：著眼於當前的點i 思考他跟其他人可以怎麼處理
dp[i][k] 0~i這些數字分成k個組 此組可以怎麼組有最小的subarray和
= dp[j][k-1] +  sum[j+1:i] ->跟其他某一派群聚
dp[i][k] = max(dp[i-1][k-1],nums[i]) -> 自成一派
*/
