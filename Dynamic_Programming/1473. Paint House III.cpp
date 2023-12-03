/*
1473. Paint House III
*/

// 優化 TC:O(m^2*n) SC:O(m*n*k)
class Solution {
    int dp[105][105][25];
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        //遍歷房子
        houses.insert(houses.begin(), 0);
        cost.insert(cost.begin(), {0});
        for(int i = 0; i<= m; i++){
            for(int j = 0; j<= m; j++){
                for(int k = 0; k <= n; k++){
                    dp[i][j][k] = INT_MAX/2;
                }
            }
        }
        //初始值 如果第一個房子被粉過就給他0 沒有的話去找要粉他的價格
        if (houses[1]!=0){
            dp[1][1][houses[1]] = 0;
        }
        else {
            for (int k=1; k<=n; k++)
                dp[1][1][k] = cost[1][k-1];
        }

        for(int i = 2; i <= m; i++){
        //遍歷造成了幾個neighbor -> block
            //已經確認了要這個顏色
            if(houses[i] != 0){
                for(int j = 1; j <= target; j++){
                    //遍歷選擇的顏色
                    int k = houses[i];
                    for(int kk = 1; kk <= n; kk++){
                        if(kk != k){
                            dp[i][j][k] = min(dp[i][j][k] ,dp[i-1][j-1][kk]);
                        }
                        else{
                            dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][kk]);
                        }
                    }
                }
            }
            else {
                for(int j = 1; j <= target; j++){
                    vector<pair<int,int>> temp;//最小值 對應顏色
                    //先將之前狀態的每個顏色最小值抓出 就不用重複遍歷了
                    for(int kk = 1; kk<=n; kk++){
                        temp.push_back({dp[i-1][j-1][kk], kk});
                    }
                    sort(temp.begin(),temp.end());

                    for(int k = 1; k<=n; k++){
                        //先將一樣的狀態加進去
                        dp[i][j][k] = dp[i-1][j][k] + cost[i][k-1];

                        if(temp[0].second != k){
                            dp[i][j][k] = min(dp[i][j][k] , temp[0].first + cost[i][k-1]);
                        }
                        else{
                            dp[i][j][k] = min(dp[i][j][k], temp[1].first + cost[i][k-1]);
                        }
                    
                    }
                }
            }
        }

        int res = INT_MAX/2;
        for(int k = 1; k<=n; k++){
            res = min(res, dp[m][target][k]);
        }
        if(res == INT_MAX/2) return -1;
        else return res; 
    }
};


// TC:O(m^2*n^2) SC:O(m*n*k)
class Solution {
    int dp[105][105][25];
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        //遍歷房子
        houses.insert(houses.begin(), 0);
        cost.insert(cost.begin(), {0});
        for(int i = 0; i<= m; i++){
            for(int j = 0; j<= m; j++){
                for(int k = 0; k <= n; k++){
                    dp[i][j][k] = INT_MAX/2;
                }
            }
        }
        //初始值
        if (houses[1]!=0)
        {
            dp[1][1][houses[1]] = 0;
        }
        else
        {
            for (int k=1; k<=n; k++)
                dp[1][1][k] = cost[1][k-1];
        }

        for(int i = 2; i <= m; i++){
        //遍歷造成了幾個neighbor -> block
            //已經確認了要這個顏色
            if(houses[i] != 0){
                for(int j = 1; j <= target; j++){
                    //遍歷選擇的顏色
                    int k = houses[i];
                    for(int kk = 1; kk <= n; kk++){
                        if(kk != k){
                            dp[i][j][k] = min(dp[i][j][k] ,dp[i-1][j-1][kk]);
                        }
                        else{
                            dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][kk]);
                        }
                    }
                }
            }
            else {
                for(int j = 1; j <= target; j++){
                    for(int k = 1; k<=n; k++){
                        for(int kk = 1; kk<=n; kk++){
                            if(kk != k){
                                dp[i][j][k] = min(dp[i][j][k] ,dp[i-1][j-1][kk] + cost[i][k-1]);
                            }
                            else{
                                dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][kk] + cost[i][k-1]);
                            }
                        }
                    }
                }
            }
        }

        int res = INT_MAX/2;
        for(int k = 1; k<=n; k++){
            res = min(res, dp[m][target][k]);
        }
        if(res == INT_MAX/2) return -1;
        else return res; 
    }
};


/*
此題突破口在於說限制了neigbor種類要到target 所以會想到每次塗的顏色會跟前面有關 無後效性->dp
想找最低cost達成目標
//遍歷房子
for(int i = 1; i <= m; i++){
//遍歷造成了幾個neighbor -> block
    //已經確認了要這個顏色
    if(house[i] != 0){
        for(int j = 1; j <= target; j++){
            //遍歷選擇的顏色
            int k = house[i];
            for(int kk = 1; kk <= n; kk++){
                if(kk != k){
                    dp[i][j][k] = min(dp[i][j][kk] ,dp[i-1][j-1][kk]);
                }
                else{
                    dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][kk]);
                }
            }
        }
    }
    else {
        for(int j = 1; j <= target; j++){
            for(int k = 1; k<=n; k++){
                for(int kk = 1; kk<=n; kk++){
                    if(kk != k){
                        dp[i][j][k] = min(dp[i][j][kk] ,dp[i-1][j-1][kk] + cost[i][k]);
                    }
                    else{
                        dp[i][j][k] = min(dp[i][j][k],dp[i-1][j][kk] + cost[i][k]);
                    }
                }
            }
        }
    }
}
*/
