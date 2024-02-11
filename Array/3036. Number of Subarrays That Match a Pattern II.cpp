/*
3036. Number of Subarrays That Match a Pattern II
*/

// TC:O(m+n) SC:O(m+n)
class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        string A;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] > nums[i-1]){
                A.push_back('A');
            }
            else if(nums[i] == nums[i-1]){
                A.push_back('B');
            }
            else A.push_back('C');
        }
        
        string B;
        for(auto x : pattern){
            if(x == 1) B.push_back('A');
            else if(x == 0) B.push_back('B');
            else B.push_back('C');
        }
        // 看pattern跟arr有多少個match
        vector<int> suf = preprocessor(B);
        
        int n = A.size();
        int m = B.size();
        if(n < m) return 0;
        
        int res = 0;
        vector<int> dp(n);
        dp[0] = (B[0] == A[0]);
        
        if(m == 1 && dp[0] == 1) res += 1;
        
        for(int i = 1; i < n; i++){
            int j = dp[i-1];
            while(j > 0 && A[i] != B[j]){
                j = suf[j-1];
            }
            
            dp[i] = j + (A[i] == B[j]);
            if(dp[i] == m){
                res += 1;
            }
        }
        
        return res;
    }
    vector<int> preprocessor(string& s){
        int n = s.size();
        vector<int> suffix(n,0);
        suffix[0] = 0;
        for(int i = 1; i<n; i++){
            int j = suffix[i-1];
            while(j > 0 && s[i] != s[j]){
                j = suffix[j-1];
            }
            suffix[i] = j + (s[i] == s[j]);
        }

        return suffix;
    }
};

/*
此題再說 pattern 如果某index 數值為 1 nums的此數值+1的所有倍數
m = 3 pattern = [1,1]
ex : k = 1 都必須後面大於前面
k= 0 都必須兩兩相等
k = -1 都必須後面小於前面
藉由上述三個規則和出的subarray有幾個
[1 0 -1 1 1 0 -1]
*/
