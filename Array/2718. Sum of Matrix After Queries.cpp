/*
2718. Sum of Matrix After Queries
*/

// TC:O(m*n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long matrixSumQueries(int n, vector<vector<int>>& queries) {
        vector<bool> row(n);
        int count_row = 0;
        vector<bool> col(n);
        int count_col = 0;

        int m = queries.size();
        LL sum = 0;
        for(int i = m-1; i >= 0; i--){
            int a = queries[i][0];
            int b = queries[i][1];
            int c = queries[i][2];
            //改row
            if(a == 0){
                //代表改過了
                if(row[b] == 1) continue;
                row[b] = 1;
                count_row += 1;
                sum += c * (n-count_col);
            }
            //改col
            else {
                if(col[b] == 1) continue;
                col[b] = 1;
                count_col += 1;
                sum += c * (n-count_row);
            }
        }

        return sum;
    }
};

/*
0:代表改row
1:代表改col 
第二個參數代表改第幾行or列 
第三個參數代表改什麼數字 
問說最後加總起來是多少
因為從前面開始遍歷 會overwrite之前的狀態 所以反著做 但如果每次都要去紀錄數字那又會超時 (n*m)^2
但如果我們用一個count_row count_col去紀錄總共填了多少行列了 要改row時只要去看哪些col 已經被填充過不能改 用乘法方式計算出他應當累加的總和
*/
