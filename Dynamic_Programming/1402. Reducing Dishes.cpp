/*
1402. Reducing Dishes
*/

// Greedy TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(),satisfaction.end());
        int n = satisfaction.size();
        vector<int> suf(n+1);
        for(int i = n-1; i >= 0; i--){
            suf[i] = suf[i+1] + satisfaction[i];
        }

        int cost = 0;
        int res = 0;
        for(int i = n-1; i >= 0; i--){
            cost += suf[i];
            res = max(res, cost);
        }

        return res;
    }
};

//  DP TC:O(n^2 + nlgn) SC:O(n^2)
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(),satisfaction.end());
        int n = satisfaction.size();
        satisfaction.insert(satisfaction.begin(), -1);
        vector<vector<int>> choose(n+1, vector<int>(n+1,INT_MIN/2));
        vector<vector<int>> noChoose(n+1, vector<int>(n+1,INT_MIN/2));
        
        noChoose[0][0] = 0;//一開始什麼都沒有選擇0個
        choose[0][0] = 0; // 一開始什麼都沒有選擇0個 合法
        for(int i = 1; i <= n; i++){
            noChoose[i][0] = 0;
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= i; j++){
                choose[i][j] = max(choose[i-1][j-1], noChoose[i-1][j-1]) + satisfaction[i] * j;
                noChoose[i][j] = max(choose[i-1][j], noChoose[i-1][j]);
            }
        }

        int res = 0;
        for(int j = 0; j <= n; j++){
            res = max(res,max(choose[n][j], noChoose[n][j]));
        }

        return res;
    }
};

/*
求數值與第幾項乘法後的總和最大 並且可任意刪除一些東西
1.首先先排序 然後就是選與不選兩種狀態
dp[i][j] i:截至目前為止 選到第j項的最大值 選 or 不選->雙狀態
2.還有一個更棒的解法greedy 
 一樣是先排序 再用後序數組不斷累加回去求過程中的最大值 累加過程中就剛好最大的數字會逐漸多他應該多的乘積數
 [-1,-8,0,5,-9] -> [-9, -8, -1, 0, 5]
*/
