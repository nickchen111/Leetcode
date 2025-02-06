// TC:O(n) SC:O(1)
class Solution {
public:
    bool winnerOfGame(string colors) {
        int n = colors.size(), i = 0, cnt[2]{};
        while(i < n) {
            int start = i;
            while(i + 1 < n && colors[i] == colors[i+1]) i += 1;
            cnt[colors[i] - 'A'] += max(0, i - start + 1 - 2);
            i += 1;    
        }
        
        return cnt[0] > cnt[1];
    }
};
