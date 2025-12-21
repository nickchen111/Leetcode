class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int res = 0;
        vector<bool> check(n);
        for(int i = 0; i < strs[0].size(); i++){
            auto check_new = check;
            bool flag = 1;
            bool flag2 = 1;
            for(int j = 1; j < n; j++){
                if(check_new[j-1] == 1) continue;
                else if(strs[j][i] < strs[j-1][i]){
                    res += 1;
                    flag2 = 0;
                    flag = 0;
                    break;
                }
                //有這種曖昧不明的 就還是要比較到下一位
                else if(strs[j][i] == strs[j-1][i]){
                   flag = 0;
                }
                else {
                    check_new[j-1] = 1;
                }
            }
            if(flag) break;
            if(flag2) {
                check = check_new;
            }
        }

        return res;
    }
};