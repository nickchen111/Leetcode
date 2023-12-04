/*
2661. First Completely Painted Row or Column
*/

// TC:O(m*n) SC:O(m+n+m*n)
class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int m = mat.size(); int n = mat[0].size();
        //紀錄mat上的數字都坐落在哪個x y上
        unordered_map<int,pair<int,int>> pos;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                pos[mat[i][j]] = {i,j};
            }
        }
        vector<int> row(m);
        vector<int> column(n);
       
        for(int i = 0; i < arr.size(); i++){
            int x = pos[arr[i]].first, y = pos[arr[i]].second;
            row[x] += 1;
            column[y] += 1;
            if(row[x] == n || column[y] == m) return i;
        }

        return -1;
    }
};

/*
此題在問最先被塗滿row || column 的欄位是在arr idx上的哪個
賓果遊戲！？ 
arr 按照順序開獎 mat為你的格子
Hash Map 紀錄你的格子的值都是在哪些位置上
兩個vector去紀錄row column被選擇的情況 當某個row or column被選滿了 就回傳當前遍歷到的arr位置
*/
