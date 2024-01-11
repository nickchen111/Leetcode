/*
2321. Maximum Score Of Spliced Array
*/

// Kadane TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        // kadane 做兩次
        int n = nums1.size();
        vector<int> gain1;
        vector<int> gain2;
        for(int i = 0; i < n; i++){
            gain1.push_back(nums2[i]-nums1[i]);
            gain2.push_back(nums1[i]-nums2[i]);
        }

        LL sum1 = accumulate(nums1.begin(), nums1.end(), 0LL) + kadane(gain1);
        LL sum2 = accumulate(nums2.begin(), nums2.end(), 0LL) + kadane(gain2);

        return max(sum1, sum2);
    }

    LL kadane(vector<int>& gain){
        LL maxVal = 0;
        LL curSum=  0;
        for(int i = 0; i < gain.size(); i++){
            curSum += gain[i];
            if(curSum < 0) curSum = 0;
            maxVal = max(maxVal, curSum);
        }

        return maxVal;
    }
};

// DP 未優化 
class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<vector<int>> dp_1(n, vector<int>(3,0));
        vector<vector<int>> dp_2(n, vector<int>(3,0));
        dp_1[0][0] = nums1[0], dp_1[0][1] = nums2[0], dp_1[0][2] = INT_MIN;
        dp_2[0][0] = nums2[0], dp_2[0][1] = nums1[0], dp_2[0][2] = INT_MIN;

        for(int i = 1; i < n; i++){
            dp_1[i][0] = dp_1[i-1][0] + nums1[i];
            dp_1[i][1] = max(dp_1[i-1][0] + nums2[i], dp_1[i-1][1] + nums2[i]);
            dp_1[i][2] = max(dp_1[i-1][2] + nums1[i], dp_1[i-1][1] + nums1[i]);//收手不拿了 之後只拿自己的
            dp_2[i][0] = dp_2[i-1][0] + nums2[i];
            dp_2[i][1] = max(dp_2[i-1][0] + nums1[i], dp_2[i-1][1] + nums1[i]);
            dp_2[i][2] = max(dp_2[i-1][2] + nums2[i], dp_2[i-1][1] + nums2[i]);//收手不拿了 之後只拿自己的
        }

        int res = INT_MIN;
        for(int j = 0; j <= 2; j++){
            res = max(max(res,dp_1[n-1][j]), dp_2[n-1][j]);
        }

        return res;
    }
};

// DP 優化 TC:O(n) SC:O(6)
class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        
        int dp_1_nochange = nums1[0], dp_1_change = nums2[0], dp_1_change2 = INT_MIN;
        int dp_2_nochange = nums2[0], dp_2_change = nums1[0], dp_2_change2 = INT_MIN;

        for(int i = 1; i < n; i++){
            auto dp_1_tmp_nochange = dp_1_nochange, dp_1_tmp_change = dp_1_change, dp_1_tmp_change2 = dp_1_change2;
            auto dp_2_tmp_nochange = dp_2_nochange, dp_2_tmp_change = dp_2_change, dp_2_tmp_change2 = dp_2_change2;

            dp_1_nochange = dp_1_tmp_nochange + nums1[i];
            dp_1_change = max(dp_1_tmp_nochange + nums2[i], dp_1_tmp_change + nums2[i]);
            dp_1_change2 = max(dp_1_tmp_change2 + nums1[i], dp_1_tmp_change + nums1[i]);//收手不拿了 之後只拿自己的
            dp_2_nochange = dp_2_tmp_nochange + nums2[i];
            dp_2_change = max(dp_2_tmp_nochange + nums1[i], dp_2_tmp_change + nums1[i]);
            dp_2_change2 = max(dp_2_tmp_change2 + nums2[i], dp_2_tmp_change + nums2[i]);//收手不拿了 之後只拿自己的
        }

        int res = INT_MIN;
        res = max(dp_1_nochange, dp_1_change);
        res = max(res, dp_1_change2);
        res = max(res, dp_2_nochange);
        res = max(res, dp_2_change);
        res = max(res, dp_2_change2);

        return res;
    }
};

/*
給你兩個數組 可以任意交換兩數組的某段區間一次 也可以不換
問說兩個數組的總和取最大 最大可以是多少
dp[i][0 or 1] 直到某段區間為止 可以獲得的最大值 選擇就是兩個數組其中之一 
兩個dp並進 一個是專門nums1 一個nums2
此題可以用DP暴力做 或者聰明一點可以想到對兩個數組而言都是要求區間的增量可以最大 那就轉化成kadane算法了
*/
