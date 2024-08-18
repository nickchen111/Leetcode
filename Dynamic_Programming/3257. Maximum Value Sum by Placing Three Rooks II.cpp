/*
3257. Maximum Value Sum by Placing Three Rooks II
*/

// TC:O(m*n*3*3) SC:O(n)
class Solution {
    using LL = long long;
    array<pair<int,int>, 3> p;
    int m, n;
public:
    long long maximumValueSum(vector<vector<int>>& board) {
        m = board.size();
        n = board[0].size();
        vector<array<pair<int, int>, 3>> suf(m);
        ranges::fill(p, make_pair(INT_MIN,-1));
        for (int i = m - 1; i > 1; i--) {
            update(board[i]);
            suf[i] = p;
        }

        LL res = LLONG_MIN/2;
        ranges::fill(p, make_pair(INT_MIN,-1));
        for(int i = 1; i < m-1; i++){
            update(board[i-1]);
            for(int k = 0; k < 3; k++){
                int j = arr[i][k]; 
                for(auto &[val1,j2] : p){
                    for(auto &[val2, j3] : suf[i+1]){
                        if(j != j2 && j2 != j3 && j3 != j){
                            res = max(res, (LL) val1 + val2 + board[i][j]);
                            break;
                        }
                    }
                }
            }
        }

        return res;

    }
    void update(vector<int>& row){
        for(int j = 0; j < row.size(); j++){
            int val = row[j];
            if(val > p[0].first){
                if(j != p[0].second){
                    if(j != p[1].second){
                        p[2] = p[1];
                    }
                    p[1] = p[0];
                }
                p[0] = {val, j};
            }
            else if(j != p[0].second && val > p[1].first){
                if(j != p[1].second){
                    p[2] = p[1];
                }
                p[1] = {val, j};
            }
            else if(j != p[0].second && j != p[1].second && val > p[2].first){
                p[2] = {val,j};
            }
        }
    }
};
