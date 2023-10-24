/*
45. Jump Game II
*/


//greedy TC:O(n) SC:O(1)
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;

        //不需要真的用一個容器存放層級遍歷的結果 只要知道他的頭尾就好
        int start = 0; int end = 0;
        int step = 0;
        while(start <= end){
            int end_new = end;
            for(int i = start; i<=end; i++){
                end_new = max(end_new, i+nums[i]);//看每一步最遠可以到哪
                if(end_new >=n-1) return step+1;
            }
            step++;
            start = end+1;//為下一層做準備
            end = end_new;
        }

        return -1;
    }
};

//dp TC:O(n^2) SC:O(n)
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        vector<int> dp(n, INT_MAX/2);
        dp[0] = 0;
        for(int i = 1; i<n; i++){
            for(int j = i-1; j>=0; j--){
                if(j+nums[j] >=i) dp[i] = min(dp[i], dp[j]+1);
            }
        }

        return dp[n-1];
    }
};


/*
此題想求最少可以用幾步跳到終點
兩個方法 1. greedy 2.dp
greedy 有點像BFS層級遍歷 
x [XX] {YYY} (OOO)
2. dp
定義 dp[i]走到i最少需要幾步
*/
