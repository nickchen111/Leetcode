/*
125. Valid Palindrome
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isPalindrome(string s) {
        string cur= "";
        for(int i = 0; i<s.size(); i++){
            if(isalnum(s[i])){
                cur+=tolower(s[i]);
            }
        }

        int n = cur.size();
        int left = 0; int right = n-1;
        while(left < right){
            if(cur[left] == cur[right]){
                left++; 
                right--;
            }
            else return false;
        }

        return true;
    }
};

/*
主要就是要會 isalnum, tolower操作
*/
