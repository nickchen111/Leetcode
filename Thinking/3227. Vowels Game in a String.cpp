/*
3227. Vowels Game in a String
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    bool doesAliceWin(string s) {
        string s1;
        int start = -1;
        int end = s.size()-1;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
                s1 += s[i];
            }
        }
        
        int n = s1.size();
        if(n == 0) return false;
        else return true;
    }
};

/*
A 勝利條件是 讓對方 剩下讓他只有一個母音可以選擇
B 的話是讓字串沒有母音
leetcode -> eeoe
xxxxxx 奇偶數的話必贏 除了 0個
*/
