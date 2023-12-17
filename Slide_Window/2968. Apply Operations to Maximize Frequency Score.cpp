/*
2968. Apply Operations to Maximize Frequency Score
*/

// Slide window + Presum + Binary Search TC:O(n + nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<LL> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + nums[i-1];
        }
        
        int i = 0;
        int j = 0;
        int res = 0;
        while(j < n){
            int mid = i + (j - i + 1)/2;
            int midVal = nums[mid];
            LL leftSum = presum[mid] - presum[i];
            LL rightSum = presum[j+1] - presum[mid+1];
            
            int leftLen = mid - i;
            int rightLen = j - mid;
            LL cost = ((LL)leftLen*nums[mid] - leftSum) + (rightSum - (LL)rightLen*nums[mid]);
            
            if(cost <= k){
                res = max(res, j-i+1);
                j++;//擴大窗口
            }
            else i++;//縮小窗口
            
        }
        
        return res;
        
    }
};

/*
此題說你可以對同一個數字加一or減一很多次 但是你有個使用限制 加加減減總次數不能超過k
問說怎麼樣的操作能讓數組內重複的元素最多
此題週賽的時候看到被加一減一給誤導了 其實只要去想我讓某個數字當作不變的那項 讓大家配合我 那麼所需花費的cost為多少
還有一個考點就是無腦考慮每段可以區間的中位數 因為中間肯定是離左離右相差diff可以保持較小的好選擇
Slide window + Presum + Binary Search
*/
