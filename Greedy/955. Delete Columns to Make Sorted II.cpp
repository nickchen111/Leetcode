/*
955. Delete Columns to Make Sorted II
*/

// TC:O(n*m) SC:O(n)
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

/*
這題給你許多字串 放在一個數組內 並且每個字串等長
這題說你可以任意刪除所有字串的某index問最少需要刪除幾次讓他變成lexicographic order
要變成lexicographcial order
n = 100 , 總共也會有100個字串
先看最前頭的元素大小 如果不符合就刪除 一直去比較直到符合的時候 
如何處理等於的狀況 就要比較下一個 1. 有下一個就比較一下 2. 沒有也可以就繼續走
比較麻煩的是 如果有等於的狀況但是在上一層就是合法狀態那也無仿 但如果上一層是false 那就要繼續比下一層
所以我的作法是在造一個check數組 然後每一層都有一個check_new數組 只要當下的狀況沒有違法的 我就可以更新check數組
但如果有我就不更新 並且利用flag 來判斷是否都合法了就不用再往下走 flag2判斷是否可以在這層結束後更新check數組
1.flag 判斷這一層是否全部合法 而且沒有等於的狀況 就算有上一層也已經合法了所以沒差
2. flag2 判斷這一層的結果可能有更多合法的狀況是否可以更新回check數組 如果遭到刪除那就不行
*/
