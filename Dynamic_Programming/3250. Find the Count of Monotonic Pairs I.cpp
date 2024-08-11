/*
3250. Find the Count of Monotonic Pairs I
*/

// 最優解 TC:O(n*m) SC:O(m*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size();
        int maxnum = *max_element(nums.begin(), nums.end());
        vector<vector<LL>> dp(n+1, vector<LL>(maxnum+1));
        nums.insert(nums.begin(), -1);
        for(int i = 0; i <= nums[1]; i++){
            dp[1][i] = 1;
        }
        
        for(int i = 2; i <= n; i++){
            int maxVal = max(nums[i], nums[i-1]);
            vector<LL> presum(maxVal+1);
            for(int k = 0; k <= maxVal; k++){
                presum[k] = (k-1 < 0 ? 0 : presum[k-1]) + dp[i-1][k];
            }
            for(int j = 0; j <= nums[i]; j++){
                int minVal = min(j, nums[i-1]-nums[i]+j);
                dp[i][j] = (minVal >= 0 ? presum[minVal] : 0);
                dp[i][j] %= M;
            }
        }
        
        int res = 0;
        for(int i = 0; i <= nums[n]; i++){
            res = (res + dp[n][i]) % M;
        }
    
        
        return res;
    }
};


/*
k代表之前的數字, j代表這次要求的數字
k <= j
nums[i-1]-k >= nums[i]-j -> k <= nums[i-1] - nums[i] + j; k代表之前的數字
k = min(j, nums[i-1] - nums[i] + j) 
為何不能直接用j-1 來求前綴和 因為j-1的數值可能不滿足題目要求的規律 這就是為什麼這題要用數學公式來求出
*/


// 次佳解 TC:O(n*m^2) SC:O(m*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size();
        vector<vector<LL>> dp(n+1, vector<LL>(51));
        nums.insert(nums.begin(), -1);
        for(int i = 0; i <= nums[1]; i++){
            dp[1][i] = 1;
        }
        
        for(int i = 2; i <= n; i++){
            int cur = nums[i];
            for(int j = 0; j <= min(cur, nums[i-1]); j++){
                int nums2_limit = nums[i-1] - j;
                if(dp[i-1][j]){
                    // j 是之前較小的limit, nums2_limit是up數組較大的
                    for(int k = cur; k >= j; k--){
                        if(nums2_limit >= cur-k){
                            dp[i][k] = (dp[i][k] + dp[i-1][j]) % M;
                        }
                        else break;
                    }
                }
            }
        }
        
        int res = 0;
        for(int i = 0; i <= 50; i++){
            res = (res + dp[n][i]) % M;
        }
        
        return res;
    }
};

/*
要讓兩個數組 一個非嚴格單調遞增 一個遞減
並且兩者相加等於原來數組 問說有幾對這種數組
dp[i][前面是多少數字] 走到i的時候有幾對這種數組
ex : i = 5, 0+5, 1+4, 2+3, 3+2, 4+1,5+0....
dp[i-1][1]

2 3 2 
0 : 2
1 : 1
2 : 0

0 -> 0 : 3
1 -> 1 : 2
2 -> 2 : 1
*/
