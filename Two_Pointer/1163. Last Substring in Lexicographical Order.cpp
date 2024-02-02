/*
1163. Last Substring in Lexicographical Order
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string lastSubstring(string s) {
        int n = s.size();
        int i = 0, j = 1, k = 0;
        char ch = s[0];
        while(j+k < n){
            if(s[i+k] == s[j+k]) k++;
            else if(s[i+k] < s[j+k]){
                i = max(i+k+1,j);
                j = i+1;
                k = 0;
            }
            else {
                j += k+1;
                k = 0;
            }
        }

        return s.substr(i);
    }
};


/*
首先肯定會想要比較所有最大字元出現的位置之後的字元才能判斷誰才是最大的
雙指針開始比較 如果都相同兩指真的長度往後走 一旦 前面的大於後面的 j 重新設定為已經走過的元素+1
但如果前面的比較小 就需要看你走的路徑哪點是最大的是否走超過j ? 如果沒超過就以j為出發點
超過的話代表後面某一個元素會跟j一樣大並且構造出更佳的答案
ex : x b b c x b b c {x c b c}
*/
