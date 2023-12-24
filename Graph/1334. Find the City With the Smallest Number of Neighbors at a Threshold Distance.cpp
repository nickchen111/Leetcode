/*
1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
*/

// TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dp(n,vector<int>(n,INT_MAX/3));

        for(int i = 0; i < n; i++){
            dp[i][i] = 0;
        }
        for(int i = 0; i < edges.size(); i++){
            dp[edges[i][0]][edges[i][1]] = edges[i][2];
            dp[edges[i][1]][edges[i][0]] = edges[i][2];
        }
        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        

        //找出最少數量的城市
        int minNumber = INT_MAX;
        vector<int> candidate;
        for(int i = 0; i < n; i++){
            int count = 0;
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                if(dp[i][j] <= distanceThreshold) count++;
            }
            if(count < minNumber){
                candidate.clear();
                candidate.push_back(i);
                minNumber = count;
            }
            else if(count == minNumber){
                candidate.push_back(i);
            }
        }

        int maxNum = INT_MIN;
        for(int i = 0; i < candidate.size(); i++){
            if(candidate[i] > maxNum){
                maxNum = candidate[i];
            }
        }

        return maxNum;

    }
};


/*
此題想找某個city他所連結的city數量要盡量少 並且跟每個城市的距離不超過門檻值
如果有很多這樣的城市 return 數字最大的
1. 鄰接表可以算出每個城市連到多少個城市
2. 要算距離的話還是要用 floyd

*/
