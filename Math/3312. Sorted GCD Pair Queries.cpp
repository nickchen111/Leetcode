/*
3312. Sorted GCD Pair Queries
*/

// TC:O((m+k)lgm + n) m 是最大的數字, n是nums數組長度, k是queris次數 SC:O(m)
class Solution {
    using LL = long long;
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int n = nums.size();
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> cnt_x(maxVal + 1);
        for(auto &x : nums){
            cnt_x[x] += 1;
        }
        
        
        vector<LL> cnt_gcd(maxVal+1);
        for(int i = maxVal; i > 0; i--){
            LL count = 0;
            for(int j = i; j <= maxVal; j+=i){
                count += cnt_x[j];
                cnt_gcd[i] -= cnt_gcd[j]; // gcd 是2i, 3i,4i的數是不能統計上去的 一開始的i因為是倒序遍歷所以是0就沒差
            }
            cnt_gcd[i] += (LL)count*(count-1)/2; // c個數取兩個數來配對
        }
        
        vector<LL> presum(maxVal+1);
        for(int i = 1; i <= maxVal; i++){
            presum[i] = presum[i-1] + (LL)cnt_gcd[i];
        }
        
        int m =  queries.size();
        vector<int> res(m);
        // x x x x x 
        for(int i = 0; i < m; i++){
            LL curNum = queries[i];
            auto iter = upper_bound(presum.begin(), presum.end(), curNum);
            res[i] = iter - presum.begin();
        }
        
        return res;
        
        
    }
};


/*
要如何確定出來的數字是誰 二分!? 二分過程要如何快速定位到第k小的數字 因為現在是要GCD所以其實很難搞
把所有GCD出現次數算出來，就可以presum + 二分 
GCD問題 -> 枚舉GCD以其倍數
枚舉gcd = 2 看 2,4,6,8,...的數有多少個
*/ 
