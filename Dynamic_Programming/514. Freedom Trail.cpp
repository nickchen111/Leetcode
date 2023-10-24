/*
514. Freedom Trail
*/

//TC:O(n*m^2) SC:O(n*m)
class Solution {
    //iterative
public:
    int findRotateSteps(string ring, string key) {
        int m = ring.size(); int n = key.size();
        unordered_map<char, vector<int>> letter2pos;
        vector<vector<int>> dp(n, vector<int>(m, INT_MAX/2));
        //把字的位置都先搞清楚了
        for(int i = 0; i<m; i++){
            letter2pos[ring[i]].push_back(i);
        } 
        for(int cur_pos: letter2pos[key[0]]){
            dp[0][cur_pos] = min(cur_pos, m-cur_pos);
        }

        for(int i = 1; i < n; i++){//從回合開始
            for(int cur_pos:letter2pos[key[i]])
                for(int prev_pos: letter2pos[key[i-1]]){
                    //因為遍歷很多prev_pos要挑個最小值
                    dp[i][cur_pos] = min(dp[i][cur_pos],dp[i-1][prev_pos]+min(abs(cur_pos-prev_pos), m-abs(cur_pos-prev_pos)));
                }
        }
        
        int res = INT_MAX;
        for(int pos:letter2pos[key[n-1]]){
            res = min(res, dp[n-1][pos]);
        }

        return res+n;
    }
};

/*
此題的邏輯思路應為
去搜尋第一個他指定的那個字 去把這個字所在的pos算出最小可轉到他的次數 
可能是順時針或者逆時針 取最小的那個 然後根據這一項去算出下一項的最小轉到次數
dp[i][pos] = min {dp[i-1][prev_pos] + dis(pos0-prev_pos)}
dp[i][pos]: at the i round, we are going to move the letter at ring[pos] to 12 o'clock
the minimum number of steps to spell all the characters in the keyword[0:i]
*/
