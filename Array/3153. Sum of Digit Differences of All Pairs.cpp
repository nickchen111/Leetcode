/*
3153. Sum of Digit Differences of All Pairs
*/

// 3153. Sum of Digit Differences of All Pairs
class Solution {
    using LL = long long;
public:
    long long sumDigitDifferences(vector<int>& nums) {
        vector<vector<int>> count(10, vector<int>(10));
        
        int n = nums.size();
        
        LL res = 0;
        for(int i = 0; i < n; i++){
            int cur = nums[i];
            int tmp = 0;
            LL presum = i;
            while(cur != 0){
                int mod = cur%10;
                res += presum - count[tmp][mod];
                count[tmp][mod] += 1;
                tmp += 1;
                cur /= 10;
            }
        }
        
        return res;
    }
};

/*
去判斷所有對的每個十進位位置上不同的數量有多少個
10^9 -> 9位數
走到一個數字的時候往回看 10個數字 0-10有多少個即可 
那只需要一個數組紀錄每一位數上的每個數字的(0-9)數量
可以n*10*10 -> 10^7 
還可以在優化 因為每一位數上往回看的數字數量是固定的 代表只需要看當下數字之前的數量 - 目前這個位數上除了自己以外的數字有多少個
*/
