/*
54. Spiral Matrix
*/


// TC:O(m*n) SC:O(m*n)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(); int n = matrix[0].size();
        int upper_bound = 0; int lower_bound = m-1;
        int left_bound = 0; int right_bound = n-1;

        vector<int> res;
        while(res.size() < m*n){
            //上面那row從左到右
            //需確定是否存在此行
            if(upper_bound <= lower_bound){
                for(int j = left_bound; j<=right_bound; j++){
                    res.push_back(matrix[upper_bound][j]);
                }
                upper_bound++;
            }

            //右邊column 從上到下
            if(left_bound <= right_bound){
                for(int i = upper_bound; i<=lower_bound; i++){
                    res.push_back(matrix[i][right_bound]);
                }
                right_bound--;
            }
            //下面row從右到左
            if(upper_bound <= lower_bound){
                for(int j = right_bound; j>=left_bound; j--){
                    res.push_back(matrix[lower_bound][j]);
                }
                lower_bound--;
            }
            //左邊column 從下到上
            if(left_bound <= right_bound){
                for(int i = lower_bound; i>=upper_bound; i--){
                    res.push_back(matrix[i][left_bound]);
                }
                left_bound++;
            }
        }

        return res;
    }
};

/*
此題為一考你花式遍歷的題目
按照題目給的條件去一個一個遍歷 然後開始將條件慢慢限縮
*/
