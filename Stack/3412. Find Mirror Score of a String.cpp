// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long calculateScore(string s) {
        // 紀錄每個字母的位置
        vector<vector<int>> pos(26);
        int n = s.size();
        LL res = 0;
        for(int i = 0; i < n; i++) {
            // 找出關鍵鏡像字
            char mi = abs(s[i]-'a' - 25) + 'a';
            if(pos[mi-'a'].size() > 0) {
                res += (i - pos[mi-'a'].back());
                pos[mi-'a'].pop_back();
            }
            else {
                pos[s[i]-'a'].push_back(i);
            }
        }
        
        return res;
    }
};
