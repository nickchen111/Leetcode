/*
1616. Split Two Strings to Make Palindrome
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size();
        if(n == 1) return true;
        if(a[0] == b[n-1]){
            int left = 1;
            int right = n-2;
            while(left < right){
                if(a[left] == b[right]){
                    left++;
                    right--;
                }
                else if(check(a,left, right) || check(b, left, right)) return true;
                else break;
            }
            if(left >= right) return true;
        }

        if(a[n-1] == b[0]){
            int left = 1;
            int right = n-2;
            while(left < right){
                if(b[left] == a[right]){
                    left++;
                    right--;
                }
                else if(check(a,left, right) || check(b, left, right)) return true;
                else break;
            }
            if(left >= right) return true;
        }
        if(check(a, 0, n-1) || check(b, 0, n-1)) return true;

        return false;
    }
    bool check(string& s, int left, int right){
        while(left < right){
            if(s[left] == s[right]){
                left++;
                right--;
            }
            else return false;
        }

        return true;
    }
};

/*
分割兩個字串的同個位置然後拼接他們 讓他們其中一可以變成回文串
回文串定義為 abba
想法就會是兩邊都從頭跟尾巴開始比 如果不相同就看自己or對方剩下的狀況 如果某一方是回文那就代表可以拼接成功
A: x x x | x x x x x | x x x
B: x x x | x x x x x | x x x
A打頭A1 + B2 + B3 or A1 + A2 + B3 
B打頭B1 + A2 + A3 or B1 + B2 + A3 

*/
