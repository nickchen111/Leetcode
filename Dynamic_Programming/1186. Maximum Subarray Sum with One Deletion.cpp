/*
1186. Maximum Subarray Sum with One Deletion
*/

// DP 雙狀態 TC:O(n) SC:O(2*n)
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(2));
        //base case
        dp[0][0] = arr[0];
        dp[0][1] = 0;//定義是非空數組 但是此項不會造成overflow所以可以這樣寫
        int res = arr[0];
        for(int i = 1; i<n; i++){
            dp[i][0] = max(dp[i-1][0]+arr[i], arr[i]);//代表選擇不刪的狀態
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]+arr[i]); //代表選擇刪掉的 但是可能是刪當下那個數 or 更早之前已刪
            res = max(res, max(dp[i][0], dp[i][1]));
        }
        return res;
    }
};

// Kadane 類似貪心 優化空間時間 
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        //base case
        int status1 = arr[0];
        int status2 = 0;//定義是非空數組 但是此項不會造成overflow所以可以這樣寫
        int res = arr[0];
        for(int i = 1; i<n; i++){
            status2 = max(status1, status2+arr[i]); //代表選擇刪掉的 但是可能是刪當下那個數 or 更早之前已刪
            status1 = max(status1+arr[i], arr[i]);//代表選擇不刪的狀態
            res = max(res, max(status1, status2));
        }
        return res;
    }
};


// 前後綴分解 DP TC:O(n) SC:O(n)
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        if(n == 1) return arr[0];

        vector<int> suffix(n);
        int sum = arr[n-1];
        for(int i = n-2; i >= 0; i--){
            suffix[i] = sum;
            sum = max(sum + arr[i], arr[i]);
        }

        int res = max(suffix[0], suffix[0] + arr[0]);
        int prefix = arr[0];
        for(int i = 1; i < n-1; i++){
            res = max(res, max(prefix, max(prefix + suffix[i], suffix[i])));
            prefix = max(prefix + arr[i], arr[i]);
        }
        
        // 到了最後一位，如果前面都是負數 他就不能不取前面
        res = max(res, prefix);

        return res;
    }
};



/*
雙狀態題型
可以刪除某個數字 也就是每次的選擇可能會有刪除的狀態OR 沒刪除的狀態
dp[i][j] j只會是0 or 1 表示刪or 沒刪 定義為arr[i]之前可以有的最大sum值
the maximum sum for a non-empty subarray

尽管兩個class的时间复杂度都是O(n)，但優化後的在实际运行中可能会更快，原因可能是：
内存局部性优化： 優化後的只使用了两个额外的整数变量（status1和status2），而不需要一个额外的二维数组（dp）来存储状态信息
这可能导致更好的内存局部性，减少了内存访问的延迟，从而提高了性能。
更少的数组访问： 第一個class在每个循环迭代中都要访问dp数组，而優化後的只需访问两个整数变量。这减少了数组访问的次数，有助于提高性能。
*/
