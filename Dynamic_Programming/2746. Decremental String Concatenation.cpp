/*
2746. Decremental String Concatenation
*/

// TC:O(2^n) SC:O(2^n) 
class Solution {
    vector<string> words;
    int memo[1001][27][27];
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        //寫成直接計算的最小長度的方式
        this->words = words;
        for(int i = 0; i<1000; i++){
            for(int j = 0; j < 26; j++){
                for(int k = 0; k < 26; k++){
                    memo[i][j][k] = -1;
                }
            }
        }
        
        return words[0].size() + DFS(1, words[0][0]-'a', words[0].back()-'a');
    }

    int DFS(int i, int start, int end){
        if(i == words.size()) return 0;
        //避免abc aec ->不論頭還是尾相連都一樣結尾
        if(memo[i][start][end] != -1) return memo[i][start][end];

        int res = INT_MAX;
        int len = words[i].size();
        int new_start = words[i][0]-'a'; int new_end = words[i].back()-'a';

        if(new_start == end){
            res = min(res, len - 1 + DFS(i+1, start, new_end));
        }

        else {
            res = min(res, len + DFS(i+1, start, new_end));
        }

        if(new_end == start){
            res = min(res, len - 1 + DFS(i+1, new_start, end));
        }
        
        else res = min(res, len + DFS(i+1, new_start, end));
        
        
        memo[i][start][end] = res;

        return res;
    }
};

/* 
acd dcd brf def 只能操作n-1 = 3次 
並且每個字串 只能前一個接現在的 或者現在的接前一個
(i, start, end) i表示選了幾種  1000*26*26
*/
