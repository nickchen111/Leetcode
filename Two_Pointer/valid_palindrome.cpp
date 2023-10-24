
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

//chatgpt得出的解答 用two pointer 加上一些判斷函式 time:o(n) space:o(m)
class Solution {
public:
    bool isPalindrome(string s) {
        string cleanedstr;
        for(auto c:s){
            if(isalnum(c)){   //如果不是的話為零
            cleanedstr += tolower(c);
            }
        }
        //開始設計two pointer
        int left = 0;
        int right = cleanedstr.length()-1;
        while(left < right){
            if(cleanedstr[left] != cleanedstr[right]) return false;
            left++;
            right--; 
        }
        return true; 
    }
};
//在字符串清理过程中，我们需要额外的空间来存储新的字符串cleanedStr，其中包含字母数字字符。假设cleanedStr的长度为m，则空间复杂度为O(m)。
//字符串清理过程的时间复杂度为O(n)，其中n是字符串s的长度。在清理过程中，我们需要遍历字符串s中的每个字符，并检查其是否为字母数字字符，因此时间复杂度为O(n)。
//判断回文串的过程的时间复杂度为O(n/2)，其中n是字符串s的长度。我们使用双指针技术来遍历cleanedStr，需要最多遍历一半的字符。
//综合起来，整体的时间复杂度为O(n)。

//也可以不判斷前面的字元是否符合alnum直接做
class Solution2 {
public:
    bool isPalindrome(string s) {
        int l=0,r=s.size()-1;
        while(l<r)
        {
            if(!isalnum(s[l]))
                l++;
            else if(!isalnum(s[r]))
                r--;
            else if(tolower(s[l])!=tolower(s[r]))
                return false;
            else
            {
                l++;
                r--;
            }
        }
        return true;
    }
};


int main(){
    string s = "A man, a plan, a canal: Panama";
    Solution a;
    cout<< a.isPalindrome(s);

}