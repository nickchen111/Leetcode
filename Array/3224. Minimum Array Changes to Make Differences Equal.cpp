/*
3224. Minimum Array Changes to Make Differences Equal
*/

// TC:O(n+k) SC:O(k)
class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0;
        int j = n-1;
        vector<int> arr(k+1);
        vector<int> count(k+1);
        while(i < j){
            int diff = abs(nums[i] - nums[j]);
            arr[diff] += 1;
            int maxVal = max(nums[i], nums[j]);
            int minVal = min(nums[i], nums[j]);
            count[max(k-minVal, maxVal)] += 1;
            i++;
            j--;
        }
        
        int res = n/2;
        for(int i = 1; i <= k; i++){
            count[i] += count[i-1];
        }
        
        for(int i = 0; i <= k; i++){
            int cost = n/2 - arr[i];
            if(i-1 >= 0){
                cost += count[i-1];
            }
            
            res = min(res, cost);
        }
        
        return res;
        
    }
};

/*
要讓頭尾的數字 相減都相同 可以改數字 0-k的區間選 問說 最少需要改多少數字達到目標
0 <= nums[i] <= k <= 10^5
絕對可以經由把數字改大 讓diff 變小
至於比目前diff小的數字 就要去計算他們各自的最大範圍會是多少
這樣我們只要在traverse到所有diff的時候去判斷當下diff-1有多少比他小的最大範圍 -> presum
*/
