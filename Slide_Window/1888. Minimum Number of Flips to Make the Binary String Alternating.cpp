// TC:O(n) SC:O(n)
class Solution {
public:
    int minFlips(string s) {
        int n = s.size();
        int m = n;
        for(int i = 0; i < n; i++) s.push_back(s[i]);
        int cand1 = INT_MAX; // 0101
        n = s.size();
        int i = 0;
        int cnt = 0;
        for(int j = 0; j < n; j++) {
            if(((j % 2) && s[j] == '0') || (((j % 2) == 0) && s[j] == '1')) cnt += 1;
            if(j - i + 1 == m) {
                cand1 = min(cand1, cnt + max(0, m-n+1));
                if(((i % 2) && s[i] == '0') || (((i % 2) == 0) && s[i] == '1')) cnt -= 1;
                i++;
            }
        }
        int cand2 = INT_MAX;
        i = 0;
        cnt = 0;
        for(int j = 0; j < n; j++) {
            if(((j % 2) && s[j] == '1') || (((j % 2) == 0) && s[j] == '0')) cnt += 1;
            if(j - i + 1 == m) {
                cand2 = min(cand2, cnt + max(0, m-n+1));
                if(((i % 2) && s[i] == '1') || (((i % 2) == 0) && s[i] == '0')) cnt -= 1;
                i++;
            }
        }

        return min(cand1, cand2);
   }
};

// 可以做 將前面字移動到後面 or 將一個字翻轉 問說最少要幾次讓字串變成0101 or 1010
// 目標會是0101 or 1010
