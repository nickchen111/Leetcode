class Solution {
public:
    int minimumPushes(string word) {
        vector<int> count(26,0);
        for(auto ch : word){
            count[ch-'a'] += 1;
        }
        sort(count.rbegin(), count.rend());
        int res = 0;
        int count1 = 0;
        for(auto x : count){
            if(x != 0) count1 += 1;
            else break;
            if(count1 < 9) res = res + x;
            else if(count1 >= 9 && count1 <= 16) res += 2*x;
            else if(count1 > 16 && count1 <= 24) res += 3*x;
            else res += 4*x;
        }
        
        return res;
    }
};