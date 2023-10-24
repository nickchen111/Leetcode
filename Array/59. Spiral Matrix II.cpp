/*
59. Spiral Matrix II
*/

// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int upper_bound = 0; int lower_bound = n-1;
        int left_bound = 0; int right_bound = n-1;

        int nums = 1;//要填充的數字
        while(nums <= n*n){
            //上面那row從左到右
            //需確定是否存在此行
            if(upper_bound <= lower_bound){
                for(int j = left_bound; j<=right_bound; j++){
                    res[upper_bound][j] = nums++;
                }
                upper_bound++;
            }

            //右邊column 從上到下
            if(left_bound <= right_bound){
                for(int i = upper_bound; i<=lower_bound; i++){
                    res[i][right_bound] = nums++;
                }
                right_bound--;
            }
            //下面row從右到左
            if(upper_bound <= lower_bound){
                for(int j = right_bound; j>=left_bound; j--){
                    res[lower_bound][j] = nums++;
                }
                lower_bound--;
            }
            //左邊column 從下到上
            if(left_bound <= right_bound){
                for(int i = lower_bound; i>=upper_bound; i--){
                    res[i][left_bound] = nums++;
                }
                left_bound++;
            }
        }
        return res;
    }
};
/*
此題為54題的變形
反過來要你按照螺旋的順序去填充數字
*/
