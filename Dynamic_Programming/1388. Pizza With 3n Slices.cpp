/*
1388. Pizza With 3n Slices
*/

//TC:O(n*k) SC:O(n*k)
class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        int n = slices.size();

        return max(solve(0,n-2,n/3, slices), solve(1,n-1,n/3, slices));//看是頭不選 or 尾巴不選
    }
    int solve(int start, int end, int k, vector<int>& slices){
        //雙狀態 house robber I
        int n = slices.size();
        vector<vector<int>> dp0(n,vector<int>(k+1, 0));//the maximum gain when we do not pick the i-th slice with total j picked
        vector<vector<int>> dp1(n,vector<int>(k+1, 0));//the maximum gain when we do pick the i-th slice with total j picked

        //加上取了幾個的維度
        //考慮base case
        dp0[start][0] = 0;
        dp1[start][1] = slices[start];
        
        for(int i = start+1; i<=end; i++){
            for(int j = 1; j <= min(i-start+1,k); j++){//有可能數組的數量不到k j從已經取了1個開始
                dp0[i][j] = max(dp0[i-1][j], dp1[i-1][j]);//這裡也會越界
                dp1[i][j] = dp0[i-1][j-1]+slices[i]; //這裡可能會越界
            }
        }

        return max(dp0[end][k], dp1[end][k]);
    }
};


/*
此題難啊
第一步轉化要跟house robber II連結再一起 
第二步轉化要跟house robber I連結再一起
會發現此題的限制多了取的限制次數 肯定是 3n/3 每個人
所以在狀態轉移方程dp要多考慮一個維度代表限制次數

此題限制：
1. never pick adjacent slcies->取一個扔兩個翻譯成不取相鄰的元素
2.end->start wrapper up 尾巴跟頭要連結起來 -> house robber II
3. pick as many as 3n/3 slices

*/
