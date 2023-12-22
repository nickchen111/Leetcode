/*
564. Find the Closest Palindrome
*/

//  TC:O(n) SC:O(n)
class Solution {
public:
    string nearestPalindromic(string n) {
        string candidate1 = nextSmaller(n);
        string candidate2 = nextGreater(n);

        if((stoll(candidate2) - stoll(n)) >= (stoll(n) - stoll(candidate1))){
            return candidate1;
        }
        else return candidate2;
    }

    string nextSmaller(string& n){
        string s = n;
        int m = s.size();
        for(int i = 0, j = m-1; i <= j;){
            s[j--] = s[i++]; 
        }
        if(s < n) return s;

        //沒有的話就自己做一個 減法
        // x x x x 
        int carry = 1;
        for(int i = (m-1)/2; i >= 0; i--){
            int d = s[i] - '0' - carry;
            if(d >= 0){
                s[i] = d + '0';
                carry = 0;
            }
            else {
                s[i] = '9';
                carry = 1;
            }
            s[m-1-i] = s[i];
        }
        if(s[0] == '0' && m > 1) return string(m-1,'9');
        else return s;
    }

    string nextGreater(string& n){
        string s = n;
        int m = s.size();
        for(int i = 0, j = m-1; i <= j;){
            s[j--] = s[i++]; 
        }
        if(s > n) return s;

        //沒有的話就自己做一個 加法
        int carry = 1;
        for(int i = (m-1)/2; i >= 0; i--){
            int d = s[i] - '0' + carry;
            if(d <= 9){
                s[i] = d + '0';
                carry = 0;
            }
            else {
                s[i] = '0';
                carry = 1;
            }
            s[m-1-i] = s[i];
        }
        if(carry == 1){
            string str = string(m+1, '0');
            str[0] = str.back() = '1';
            return str;
        }
        else return s;
    }
};


/*
此題給你一個數字找到離他最近的為回文串的數字(不包含自己) 如果有兩個候選人 選數字較小的
如果用2697寫的brute force找會超時
要用我在比賽時的想法 經過影片學習時理解了當初盲點 如果從高位開始直接翻 翻出來的數字有可能比較大 or 小 但是答案兩個都要確認
ex : 12399 -> 直接翻 12321 但差距更小的是 12421 
但這個方法會有corner case ex : 991 -> 如果想加一 1008 但應該會是 1001比較好 直接寫一個四位數的最小回文 變小的話直接構造最大回文
*/
