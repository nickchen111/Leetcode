/*
213. House Robber II
*/

//雙狀態 TC:O(n) SC:O(1)
class Solution {
    //dual state
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];

        //第一項不選
        int rob = nums[1], norob = 0;
        int res;
        for(int i = 2; i<n; i++){
            int rob_tmp = rob, norob_tmp = norob;
            rob = norob_tmp+nums[i];
            norob = max(rob_tmp, norob_tmp);
        }
        res = max(rob,norob);

        //最後一項不選
        rob = nums[0], norob = 0;
        for(int i = 1; i<n-1; i++){
            int rob_tmp = rob, norob_tmp = norob;
            rob = norob_tmp+nums[i];
            norob = max(rob_tmp, norob_tmp);
        }
        res = max(res, max(rob, norob));

        return res;
    }
};

//區間型DP TC:O(n^2) SC:O(n^2)
class Solution {
    //區間型DP iterative
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        if(n == 1) return nums[0];

        auto dp = vector<vector<int>> (n, vector<int>(n, 0));

        //base case
        for(int i = 0; i<n; i++){
            dp[i][i] = nums[i];
        }


        for(int len = 2; len<=n; len++){
            for(int i = 0; i+len-1<n; i++){
                int j = i+len-1;
                dp[i][j] = max(nums[i]+ ((i+2>j) ? 0:dp[i+2][j]), dp[i+1][j]);
            }
        }
        
        return max(nums[0]+((n-2<2) ?0:dp[2][n-2]), dp[1][n-1]);
    }
};


/*
此題要求如果你選了第一項那麼最後一項就不能選 沒選那最後一項就可以選 可以有兩種構想 1. 將題目往雙狀態去靠攏 2. 用比較通用的寫法區間型DP
1.
N[             ]第一項不選 這樣後面就會是house robber I
[            ] N 最後一項不選 前面就變成house robber I

2. 區間型DP
dp[i][j] 在這段區間內最大可以搶到多少錢 the maximum amount of money you can rob
dp[i][j] = max(nums[i] + dp[i+2....j], dp[i+1,....j]) 縮小到一個點一個點去思考 第一家打劫or不打劫的狀態
*/
