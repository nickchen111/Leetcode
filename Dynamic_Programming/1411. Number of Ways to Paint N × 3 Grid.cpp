/*
1411. Number of Ways to Paint N × 3 Grid
*/

// TC:O(n*27*3*27*6) SC:O(27)
class Solution {
    vector<int> arr1,arr2;
public:
    int numOfWays(int n) {
        arr1.resize(3);
        arr2.resize(3);
        int M = 1e9 + 7;
        vector<int> dp(27,0);

        for(int p = 0; p < 27; p++){
            if(self(p)){
                dp[p] = 1;
            }
        }

        for(int i = 1; i < n; i++){
            auto dp_prev = dp;
            for(int p = 0; p < 27; p++){
                dp[p] = 0;
                if(!(self(p))) continue;
                for(int q = 0; q < 27; q++){
                    if(!(self(q))) continue;
                    if(cross(p,q)) 
                        dp[p] = (dp[p] + dp_prev[q]) % M;
                }
            }
        }

        int sum = 0;
        for(int p = 0; p < 27; p++){
            if(self(p)) sum = (sum + dp[p]) % M;
        }

        return sum;
    }
    bool self(int p){
        
        for(int i = 0; i < 3; i++){
            arr1[i] = (p%3);
            p /= 3;
        }

        return (arr1[0] != arr1[1] && arr1[1] != arr1[2]);
    }
    bool cross(int p, int q){
       
        for(int i = 0; i < 3; i++){
            arr1[i] = (p % 3);
            arr2[i] = (q % 3);
            p /= 3;
            q /= 3;
        }

        return (arr1[0] != arr2[0] && arr1[1] != arr2[1]  && arr1[2] != arr2[2]);
    }
};


/*
問說每一列上的相鄰顏色不能一樣並且每行也是 有三色可選
每行都只會有三列 有多少種噴法可以達到目標
dp[i][p] : 在第x回合上噴上的狀態(狀態壓縮)？ 有多少種噴法可以達到

*/
