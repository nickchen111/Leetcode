/*
1031. Maximum Sum of Two Non-Overlapping Subarrays
*/

// 4/4 DP + Kadane + Slide Window
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        vector<int> dp1(n+1, INT_MIN/2);
        vector<int> dp2(n+1, INT_MIN/2);
        dp1[0] = 0;
        dp2[0] = 0;
        // 定義成走到i為止此區間加總是多少
        int sum = 0;
        for(int i = 1; i <= n; i++){
            if(i >= firstLen){
                sum = sum + nums[i] - nums[i-firstLen];
                dp1[i] = sum;
            }
            else {
                sum += nums[i];
            }
        }

        sum = 0;
        for(int i = 1; i <= n; i++){
            if(i >= secondLen){
                sum = sum + nums[i] - nums[i-secondLen];
                dp2[i] = sum;
            }
            else sum += nums[i];
        }
        

        int res = 0;
        int maxFirst = 0;
        int maxSecond = 0;
        for(int i = 1; i <= n; i++){
            if(i >= firstLen + secondLen){
                maxFirst = max(maxFirst, dp1[i-secondLen]);
                maxSecond = max(maxSecond, dp2[i-firstLen]);
                res = max(res, max(dp2[i] + maxFirst, dp1[i] + maxSecond));
            }
        }

        return res;
    }
};

// 4/4 DP + Kadane dp定義成 走到i 為止 某個長度加總會是多大
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        vector<vector<int>> dp1(n+1, vector<int>(firstLen+1, INT_MIN/2));
        vector<vector<int>> dp2(n+1, vector<int>(secondLen+1, INT_MIN/2));

        dp1[1][1] = nums[1];
        dp2[1][1] = nums[1];
        dp1[0][0] = 0;
        dp2[0][0] = 0;
        // 定義成走到i為止 長度為 firstLen 最大可以是多少
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= min(firstLen, i); j++){
                if(j == 1){
                    dp1[i][j] = max(nums[i], dp1[i-1][j-1]+nums[i]);
                }
                else dp1[i][j] = dp1[i-1][j-1]+nums[i];
            }
            for(int j = 1; j <= min(secondLen, i); j++){
                if(j == 1){
                    dp2[i][j] = max(nums[i], dp2[i-1][j-1]+nums[i]);
                }
                else dp2[i][j] = dp2[i-1][j-1]+nums[i];
            }
        }
        int res = 0;
        int maxFirst = 0;
        int maxSecond = 0;
        for(int i = 1; i <= n; i++){
            if(i >= firstLen + secondLen){
                maxFirst = max(maxFirst, dp1[i-secondLen][firstLen]);
                maxSecond = max(maxSecond, dp2[i-firstLen][secondLen]);
                res = max(res, max(dp2[i][secondLen] + maxFirst, dp1[i][firstLen] + maxSecond));
               
            } 
        }

        return res;
    }
};


// DP + Slide Window TC:O(n) SC:O(n) dp定義成 走到某個長度為止 在他之前包含現在長度 要符合subarray定義的firstLen or secondLen 最大加總是多少
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        
        return max(helper(nums,firstLen,secondLen), helper(nums,secondLen, firstLen));
    }

    int helper(vector<int>& nums, int x, int y){
        int n = nums.size();
        vector<int> dp1(n,0); //在 i以前最大的總和是多少
        vector<int> dp2(n,0); // 在 i 以後最大的總和是多少

        int sum = 0;
        for(int i = 0;  i < n; i++){
            if(i < x){
                sum += nums[i];
                dp1[i] = sum;
            }
            else {
                sum = sum + nums[i] - nums[i-x];
                dp1[i] = max(dp1[i-1], sum);
            }
        }
        
        sum = 0;
        for(int i = n-1;  i >= 0; i--){
            if(i + y > n - 1){
                sum += nums[i];
                dp2[i] = sum;
            }
            else {
                sum = sum + nums[i] - nums[i+y];
                dp2[i] = max(dp2[i+1], sum);
            }
        }
        
        int res = 0;
        for(int i = x-1; i < n-y; i++){
            res = max(res, dp1[i] + dp2[i+1]);
        }

        return res;
    }
};

/*
此題限定兩個長度 問說這兩個長度各取一個subarray 但不能重疊 問總和最多可以多少
我的想法是既然不知道len大的策略好還是len小的好 那就兩個都試一次
*/
