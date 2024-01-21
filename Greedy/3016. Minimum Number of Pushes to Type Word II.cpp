/*
3016. Minimum Number of Pushes to Type Word II
*/

// TC:O(n + 26*lg26) SC:O(26)
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

/*
說電話號碼的數字2-9你可以隨意排列a-z上去 然後給你一串字串 如果要撥打數字2上的第3個字母就要按三次
問說最少能按多少次按完所有字串 貪心的想出現頻率最高的優先排在第一個可以排八個 超過八個的排到第二個以此類推排序下去
*/
