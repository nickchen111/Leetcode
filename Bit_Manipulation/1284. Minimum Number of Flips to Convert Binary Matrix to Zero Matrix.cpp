/*
1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
*/

// TC:O(2^(m * n) * m * n) SC:O(m*n)
class Solution {
    int m,n;
public:
    int minFlips(vector<vector<int>>& mat) {

        m = mat.size();
        n = mat[0].size();

        int res = INT_MAX;
        //用狀態壓縮表示翻轉狀態
        for(int state = 0; state < (1<<(m*n)); state++){
            if(check(state,mat)){
                res = min(res, (int)bitset<9>(state).count());
            }
        }

        return res == INT_MAX ? -1 : res;
    }

    bool check(int state, vector<vector<int>>& mat){
        auto tmp = mat;
        vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0},{0,0}};
        for(int b = 0; b < (m*n); b++){
            int t = state%2;
            state /= 2;
            if(t == 0) continue;
            int x = b / n;
            int y = b % n;
            for(int i = 0; i < dirs.size(); i++){
                int nx = x + dirs[i].first;
                int ny = y + dirs[i].second;
                if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                tmp[nx][ny] = 1 - tmp[nx][ny]; 
            }
        }
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(tmp[i][j] == 1) return false;
            }
        }

        return true;
    }
};


/*
一個元素似乎不可能主動翻兩次 被動翻應該是可以很多次
觀察這題數據規模 只有3x3大小
那就是2^9 = 512 然後每個點都可以被上下左右翻轉所以就是
2^9*5^4
*/
