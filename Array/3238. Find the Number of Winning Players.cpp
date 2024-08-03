/*
3238. Find the Number of Winning Players
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int winningPlayerCount(int n, vector<vector<int>>& pick) {
        vector<vector<int>> count(n, vector<int>(11));
        for(auto &pic : pick){
            int player = pic[0];
            int color = pic[1];
            count[player][color] += 1;
        }
        int res = 0;
        for(int i = 0; i < n; i++){
            bool flag = 0;
            for(int j = 0; j <= 10; j++){
                if(count[i][j] >= i+1){
                    res += 1;
                    flag = 1;
                    break;
                }
                if(flag) break;
            }
        }
        
        return res;
    }
};
