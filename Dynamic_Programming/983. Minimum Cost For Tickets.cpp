/*
983. Minimum Cost For Tickets
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        int k = 0;
        vector<int> dp(366,0);
    
        while(k < n){
            for(int i = 1; i <= days.back(); i++){
                //上班日
                if(i == days[k]){
                    dp[i] = min(dp[i-1]+costs[0], min(dp[max(0,i-7)]+costs[1],dp[max(0,i-30)] + costs[2]));
                    k++;
                }
                else if(i != days[k]){
                    dp[i] = dp[i-1];
                }
            }
           
        }

        return dp[days.back()];

    }
};

/*
每一天買票策略都會有三種 
1. one day 2. 7 days 3 30 days
dp[i]天數
if(i is not work day) dp[i] = dp[i-1];
if(i is work day) dp[i] = min(dp[i-1]+costs[0], min(dp[max(0,i-7)]+costs[1],dp[max(0,i-30)] + costs[2]));
這肯定是最優的 因為: i < j dp[i] <= dp[j]成立 所以不會再往後找 ex: dp[i-2] + costs[1]
*/
