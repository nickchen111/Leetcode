/*
1664. Ways to Make a Fair Array
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();
        vector<int> presum_odd(n);
        vector<int> presum_even(n);

        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                presum_even[i] = (i == 0 ? 0 : presum_even[i-1]) + nums[i];
                presum_odd[i] = (i == 0 ? 0 : presum_odd[i-1]);
            }
            else {
                presum_odd[i] = (i == 0 ? 0 : presum_odd[i-1]) + nums[i];
                presum_even[i] = (i == 0 ? 0 : presum_even[i-1]);
            }
        }        
        
        int res = 0;
        for(int i = 0; i < n; i++){
            //將現在是偶數的數字拿掉
            
            // 他後面的騎術變成偶數 前面的還是奇數 所以要剪掉 然後再加上前面的偶數
            int even = (i == 0 ? 0 : presum_even[i-1]) + presum_odd[n-1] - presum_odd[i];
            int odd = presum_even[n-1] - presum_even[i] + (i == 0 ? 0: presum_odd[i-1]);
            if(even == odd) res += 1;
        
        }

        return res;
    }
};

// 另種思維 TC:O(n) SC:O(n)
class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        vector<int> leftOdd(n + 1);
        vector<int> leftEven(n + 1);

        int even_sum = 0, odd_sum = 0;
        for(int i = 1; i <= n; i++){
            if(i % 2 == 0){
                even_sum += nums[i];
            }
            else {
                odd_sum += nums[i];
            }
            leftOdd[i] = odd_sum;
            leftEven[i] = even_sum;
        }        
        
        int res = 0;
        int rightEven = 0, rightOdd = 0;
        for(int i = n; i >= 1; i--){
            if(leftEven[i-1] + rightOdd == leftOdd[i-1] + rightEven) res += 1;
            if(i % 2 == 0){
                rightEven += nums[i];
            }
            else {
                rightOdd += nums[i];
            }
        }

        return res;
    }
};

/*
此題說刪除某一個index 後面的數值會左移 那麼左移後 更新完的數組內 奇數index 跟偶數index和相同的情況有多少個
想到用presum_even presum_odd紀錄 index 邊界問題有點小麻煩並且也要頭腦清晰地寫出加減法
另一個寫法是 leftEven[i-1] + rightOdd[i+1] == leftOdd[i-1] + rightEven[i+1]; 只要先求出left就好
*/
