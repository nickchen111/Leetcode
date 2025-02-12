/*
2826. Sorting Three Groups
*/

// 2025.02.12 
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size(), ng = 0;
        // 空間優化 O(1)
        for(int i = 0; i < n; i++) {
            int j = upper_bound(nums.begin(), nums.begin() + ng, nums[i]) - nums.begin();
            if(j == ng) {
                nums[ng] = nums[i];
                ng += 1;
            } 
            else nums[j] = nums[i];
        }
        return n - ng;
        /*
        LIS
        int n = nums.size();
        vector<int> arr;
        for(int i = 0; i < n; i++) {
            auto iter = upper_bound(arr.begin(), arr.end(), nums[i]);
            if(iter == arr.end()) {
                arr.push_back(nums[i]);
            }
            else *iter = nums[i];
        }
        return n - arr.size();
        */
    }
};


// 基本型I TC:O(n) SC:O(n)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(4,0));
        for(int j = 1; j <= 3; j++){
            dp[0][j] = (nums[0] != j);
        }

        for(int i = 1; i < n; i++){
            dp[i][1] = dp[i-1][1] + (nums[i] != 1);
            dp[i][2] = min(dp[i-1][1], dp[i-1][2]) + (nums[i] != 2);
            dp[i][3] = min(dp[i-1][2], min(dp[i-1][1],dp[i-1][3])) + (nums[i] != 3);
        }

        int res = min(dp[n-1][1],min(dp[n-1][2], dp[n-1][3]));

        return res;
    }
};

// LIS TC:O(n^2) SC:O(n)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        dp[0] = 1;
        int maxLen = 1;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[j] <= nums[i]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
        int res = n - maxLen;

        return res;
    }
};
/*
此題是想將數組內的1 2 3可任意變化成其他元素
想讓結果變成 1在左邊 2在中間 3 在右邊
但也不見得一定要有1 or 2 or 3只要遞增就可以
問說最少要操作幾次

基本型Ｉ思考 考慮每個點會接 1 2 3然後考慮他的代價為何
dp[i][1] = dp[i-1][1] + (nums[i] != 1)
dp[i][2] = min(dp[i-1][1], dp[i-1][2]) + (nums[i] != 2)
dp[i][3] = min(dp[i-1][2], dp[i-1][3]) + (nums[i] != 3)
or 類似LIS的概念 列舉出最常非遞減序列 並且減去長度 
*/
