/*
1536. Minimum Swaps to Arrange a Binary Grid
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        
        int n = grid.size();
        vector<int> zero(n);
        for(int i = 0; i < n; i++){
            int count = 0;
            for(int j = n-1; j >= 0; j--){
                if(grid[i][j] == 1) break;
                count += 1;
            }
            zero[i] = count;
        }
        int res = 0;
        for(int i = 0; i < n; i++){
            int target = n-1-i;
            int j = i;
            for(;j < n; j++){
                if(zero[j] >= target){
                    break;
                }
            }

            if(j == n) return -1;
            res += (j-i);
            for(int t = j; t >= i+1; t--){
                swap(zero[t], zero[t-1]);
            }
        }
        
        return res;
    }
};

/*
可將任意兩個相鄰row全部對調
問說最少需換幾次能讓main對角線上都是0
每次都先找到一塊都有的開始row然後找最近的column1 -> column2
need : 1 3 3 6 4 6
tar  : 6 5 4 3 2 1 
plan a : 5 steps
6 1 3 3 6 4
plan b : 3 step  + 1step
6 1 3 3 4 6
6 1 3 3 6 4
3steps
6 4 1 3 3 6
代表先選近的效果最好 所以策略是先找到滿足當前trailing zero的最近的row就直接一路換上來
*/
