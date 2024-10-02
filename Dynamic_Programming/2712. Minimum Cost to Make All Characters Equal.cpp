/*
2712. Minimum Cost to Make All Characters Equal
*/


// 次優解 DP TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long minimumCost(string s) {
        int n = s.size();
        if(n == 1) return 0;

        vector<vector<LL>> pre(n, vector<LL>(2));
        vector<vector<LL>> suf(n, vector<LL>(2));
        pre[0][0] = s[0] == '0' ? 0 : 1;
        pre[0][1] = s[0] == '1' ? 0 : 1;

        for(int i = 1; i < n; i++){
            pre[i][0] = s[i] == '0' ? pre[i-1][0] : min(pre[i-1][1],pre[i-1][0]+i) + i+1;
            pre[i][1] = s[i] == '1' ? pre[i-1][1] : min(pre[i-1][1]+i,pre[i-1][0]) + i+1;
        }
        suf[n-1][0] = s[n-1] == '0'? 0 : 1;
        suf[n-1][1] = s[n-1] == '1'? 0 : 1;
        
        for(int i = n-2; i >= 0; i--){
            suf[i][0] = s[i] == '0' ? suf[i+1][0] : min(suf[i+1][1],suf[i+1][0]+(n-i-1)) + n-i;
            suf[i][1] = s[i] == '1' ? suf[i+1][1] : min(suf[i+1][1]+(n-i-1),suf[i+1][0]) + n-i;
        }

        LL res = min(min(pre[n-1][0], pre[n-1][1]), min(suf[0][0], suf[0][1]));
        for(int i = 0; i < n-1; i++){
            res = min(res,pre[i][0] + suf[i+1][0]);
            res = min(res,pre[i][1] + suf[i+1][1]);
        }

        return res;
    }
};

