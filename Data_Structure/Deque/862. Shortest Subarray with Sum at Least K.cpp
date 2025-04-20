/*
862. Shortest Subarray with Sum at Least K
*/

// brute force TC:O(n^2) SC:O(n)
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        int presum[n+1];
        presum[0]= 0;
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+ nums[i-1];
        }

        int res = INT_MAX/2; //只想得到一種n^2的解法
        for(int i = 1; i <=n; i++){
            for(int j = i-1; j>=0;j--){
                if(i - j <= res){
                    if(presum[i] - presum[j] >= k) res = min(res, i-j);
                }
            }
        }

        return res == INT_MAX/2 ? -1:res;
    }
};

//presum+deque TC:O(n) SC:O(n)
class Solution { 
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        long long presum[n+1];
        presum[0]= 0;
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+ nums[i-1];
        }

        int res = INT_MAX/2;
        deque<int> q;
        for(int i = 0; i <= n; i++){
            while(!q.empty() && presum[q.back()] >= presum[i]){
                q.pop_back();
            }
            while(!q.empty() && presum[i] - presum[q.front()] >=k){
                res = min(res, i-q.front());
                q.pop_front();
            }
            q.push_back(i);
        }

        return res == INT_MAX/2 ? -1:res;
    }
};

/*
subarray 求區間和 可以想到用presum
xxxxixxxxj
presum[j]越大越好 presum[i]越小越好
此題難點在於如果加一加突然數字變小了 就很難界定要捨棄之前的結果或者用當前的長度繼續累加
所以可以用deque 維護單調遞增 一旦出現一個比她小的就代表目前那項優勢沒了 後面的去剪掉當前項長度還比較短
所以就Pop_back
*/
