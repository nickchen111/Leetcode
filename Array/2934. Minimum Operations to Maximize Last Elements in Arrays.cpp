/*
2934. Minimum Operations to Maximize Last Elements in Arrays
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int maxVal = max(nums1[n-1],nums2[n-1]); 
        int minVal = min(nums1[n-1],nums2[n-1]);
        int dp1 = 0, dp2 = 1;
        for(int i = n-2; i >= 0; i--){
            int a = nums1[i], b = nums2[i];
            if(max(a,b) > maxVal) return -1;
            if(min(a,b) > minVal) return -1;
            if(a > nums1[n-1] || b > nums2[n-1]) dp1++;
            if(b > nums1[n-1] || a > nums2[n-1]) dp2++;
        }

        return min(dp1,dp2);
    }
};


/*
此題說要讓最後一個元素會是兩個數組本身的最大值 你可以做index之間的交換 問最少操作幾次可以達成目標
首先要想到這個問題核心邏輯就是在讓內部元素比較跟本身數組最後一個元素大小 那麼最後一個元素有哪些選擇
有兩種case 一種是他們交換 一種是他們沒有換 那麼兩種case都去模擬看看 然後比較一下內部元素
想要交換的前提就是 某一方的非結尾數字大於本身數組結尾 那麼如果nums1[i] <= nums2[n-1] && nums2[i] <= nums1[n-1]  代表他們可以換 
如果不能換就代表無解 ， 那麼如果本身就沒有超過尾端元素 就不需交換
*/
