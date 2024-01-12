/*
2381. Shifting Letters II
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        int n = s.size();
        vector<int> count(n+1);
        for(auto shift : shifts){
            int dir = shift[2];
            //往後
            if(dir == 1){
                count[shift[0]] += 1;
                count[shift[1]+1] -= 1;
            }
            else {
                count[shift[0]] -= 1;
                count[shift[1]+1] += 1;
            }
        }
        string res;
        int shiftTimes = 0;
        for(int i = 0; i < n; i++){
            int ch = s[i]-'a';
            //這裡看來要用數學翻才會比較快
            shiftTimes += count[i];
            shiftTimes %= 26;

            int newch = ((ch + shiftTimes) + 26) % 26;
            res += (newch + 'a');
        }

        return res;

    }
};

/*
這題給了你一串要求 每次要求可能會讓給定的字串中的某區間字母改成往前or往後一個字母
ex: a -> b往後 a->z 往前一格
問說不斷shift之後字串會變成怎樣
看到當下覺得蠻明顯是差分數組 先將所有的變化紀錄起來 然後再一口氣判斷每個自是往前往後幾格
如果字母是 b 現在讓你往前翻 2個 首先往前翻26個就是回到原點 一率先取26餘數 發現說 還剩 7次 那該如何翻
b : 7 ((1-7) + 26) %26 = 20 -> z y x w v u 答案是u嗎 
那如果是往後翻 
b: 25次 (1+25)%26 變成a
a   b  c. n
-1     +1   
   +1.    -1
+1        -1 
*/
