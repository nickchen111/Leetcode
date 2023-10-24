/*
389. Find the Difference
*/


//容器做法 TC:O(n) SC:O(n)
class Solution {
public:
    char findTheDifference(string s, string t) {

        vector<int> count(26,0);
        for(int i = 0; i<s.size(); i++){
            count[s[i]-'a']++;
        }
        for(int j = 0; j<t.size(); j++){
            if(--count[t[j]-'a'] < 0) return t[j];
        }

        return ' ';
    }
};

//位操作  TC:O(n) SC:O(1)
class Solution {
public:
    char findTheDifference(string s, string t) {

        int res = 0;
        for(int i = 0; i<s.size(); i++){
            res = res^s[i];
        }
        for(int j = 0; j<t.size(); j++){
            res = res^t[j];
        }

        return res;
    }
};

/*
"此題有很多方法可做
但是時間複雜度是線性的方法目前只想到
1.用一個容器紀錄原有字元 一個迴圈++ 一個迴圈-- 最後變成 <0的那個字元就是多出來的
2.用XOR位操作 直接設定一個res = 0 做XOR 最後結果就會是落單那個"
*/
