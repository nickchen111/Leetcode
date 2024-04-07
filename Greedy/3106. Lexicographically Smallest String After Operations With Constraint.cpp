/*
3106. Lexicographically Smallest String After Operations With Constraint
*/

// TC:O(26*n) SC:O(1)
class Solution {
public:
    string getSmallestString(string s, int k) {
        int n = s.size();
        if(k == 0) return s;
        
        int sum = 0;
        string res = s;
        for(int i = 0; i < n; i++){
            char ch = s[i];
            int tmp1 = sum;
            int tmp2 = sum;
            
            for(char c = ch-1; c >= 'a'; c--){
                if(tmp1 == k){
                    break;
                }
                tmp1 += 1;
                res[i] = c;
            }
            tmp2 += (('a'-ch)+26);
            
            if(tmp1 == sum && tmp2 > k) {
                res[i] = s[i];
                continue;
            }
            
            else if(tmp2 > k) sum = tmp1;
            
            else {
                if(res[i] != 'a'){
                    res[i] = 'a';
                    sum = tmp2;
                }
                else {
                    sum = min(tmp1, tmp2);
                }
            }
        }
        
        return res;
    }
};

/*
可以選擇是 z - a or abs((a-z)+26)
希望字典序最小 並且sum <= k
所以一定從第一個檢查 a-z都試試去看
往兩個方向檢查 往前檢查 以及 往後繞一圈到a看哪個字元小 如果有a先選a 在看哪個cost小
*/
