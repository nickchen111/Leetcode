/*
446. Arithmetic Slices II - Subsequence
*/

// 正著想 TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<LL,int>> dp(n);
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                LL diff = (LL)nums[i] - (LL)nums[j];
                
                dp[i][diff] += dp[j][diff] + 1;
                res += dp[j][diff];
            }
        }

        return res;
    }
};


//反著想
class Solution {
    using LL = long long;
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        //先將每個元素位置紀錄起來
        unordered_map<int, vector<int>> map;
        for(int i = 0; i < nums.size(); i++){
            map[nums[i]].push_back(i);
        }

        auto dp = vector<vector<int>>(n, vector<int>(n,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                //去找出第一項以及他前面有多少等差數列
                LL m = (LL)nums[j]*2L - (LL)nums[i];
                if(m > INT_MAX || m < INT_MIN) continue;
                //這種結果可能很多例如 重複項
                for(int k : map[m]){
                    //確保他確實在j的前面
                    if(k < j)
                        dp[j][i] += dp[k][j] + 1;
                }
            }
        }

        int res = 0;
        for(int j = 0; j < n; j++){
            for(int i = j+1; i < n; i++){
                res += dp[j][i];
            }
        }

        return res;
    }
};

/*
至少三個數字一組 每個數字成等差
問說一個數組中可以組成多少個等差數列
都可以取的狀態
5*4*3/ 3*2*1 +5*4*3*2/4*3*2*1 + 5/5 = 16
如果是原本就等差非零
2 4 6 -> 1種
2 4 6 8 ->  3種
2 4 6 8 10 -> 7 ...
2 4 6 8 10 12 -> ? 1 + 2^1 + 2^2 + 2^3 = 15 ... 7 + 5
+2 + 4 +5
有點動態規劃的味道
如果前面的長度滿足 2以上 並且當下元素跟他的差相同 
dp[i] : nums[i]結尾的等差數列 有多少個
dp[i][diff] : nums[i]結尾的等差數列 公差為diff 有多少個
dp[i][diff] : nums[i]結尾的等差數列 (長度>=2)公差為diff 有多少個
1 3 5 7 9 -> 這次答案只能加dp[j][diff] 也就是dp[i][diff] += dp[j][diff]; res += dp[j][diff]
因為最後一個他的長度只有2

還有另外一種倒過來想的思考方式
假設你已知最後兩項 要怎麼跟前面的扯上關係
dp[j][i] += dp[k][j] + 1; 1為因為多了後面兩項
*/
