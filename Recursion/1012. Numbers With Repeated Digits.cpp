/*
1012. Numbers With Repeated Digits
*/

// O(10*n) SC:O(n)
class Solution {
    int res = 0;
public:
    int numDupDigitsAtMostN(int N) {
        string str = to_string(N);
        int n = str.size();
        for(int len = 1; len <= n-1; len++){
            res += A(10,len) - A(9, len-1);
        }

        vector<bool> visited(10);
        DFS(str, 0, visited);

        return N - res;
    }
    void DFS(string& s, int i, vector<bool>& visited){
        if(i == s.size()){
            res += 1;
            return;
        }
        int n = s.size();
        for(int d = 0; d <= 9; d++){
            if(i == 0 && d == 0) continue;
            if(visited[d]) continue;
            if(d < s[i]-'0'){
                res += A(10-i-1, n-i-1);
            }
            else if(d == s[i]-'0') {
                visited[d] = 1;
                DFS(s, i+1, visited);
            }
        }
    }
    int A(int m, int n){
        int count = 1;
        for(int i = 0; i < n; i++){
            count *= (m-i);
        }

        return count;
    }
};
