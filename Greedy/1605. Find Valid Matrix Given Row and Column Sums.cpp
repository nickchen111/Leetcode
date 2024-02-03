/*
1605. Find Valid Matrix Given Row and Column Sums
*/

// TC:O(m*n) SC:O(1)
class Solution {
    using LL = long long;
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m = rowSum.size();
        int n = colSum.size();
        vector<vector<int>> res(m, vector<int>(n));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int curMin = min(rowSum[i],colSum[j]);
                res[i][j] = curMin;
                rowSum[i] -= curMin;
                colSum[j] -= curMin;
            }
        }

        return res;
    }
};

/*
給你兩個數組 row, col代表在某i-th row column上元素的總和 
請重構出原本2d matrix上的元素
x x x 
x x x 
x x x
m , n <= 500
0 <= val <= 10^8
sum(row_sum) == sum(col_sum)
我想到的是我們可以知道上限 每個元素的上限都是他們在該行的ith的總和
[5 0 0]
[3 4 0]
[0 2 8]
這題我的想法是從頭開始遍歷元素並且賦予他當下能夠選擇的最低數值的可能性 取決於 rowSum,colSum的數值減掉我當下每行每列的總和
每一步都是貪心的構造 但是他又有來自該行該列的限制 那就取最小的 因為有題目說的限制sum(row_sum) == sum(col_sum) 最後答案肯定會對
[[5,0,0]
[2,4,1]
[1,2,7]]
*/
