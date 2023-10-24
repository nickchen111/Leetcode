/*
392. Is Subsequence

Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
A subsequence of a string is a new string that is formed from the original string by deleting some (can be none)
of the characters without disturbing the relative positions of the remaining characters. 
(i.e., "ace" is a subsequence of "abcde" while "aec" is not).


Example 1:
Input: s = "abc", t = "ahbgdc"
Output: true

Example 2:
Input: s = "axc", t = "ahbgdc"
Output: false
*/

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


//這招是自己想的錯誤答案 遇到string = aaaaaa; string = bbaaaa這種重複字元的就會失敗 因為find會從頭開始找 找到一樣的位置==
class Solution {
public:
    bool isSubsequence(string s, string t) {
        int n = s.length();
        unordered_map<char, int> map;
        for(int i = 0; i < n; i++){
            int p = t.find(s[i]);  // find 搜出來的index為unsigned int type 如果是array就是address了
            map[s[i]] = p;
            if(t.find(s[i]) == t.npos) return false;
        }
        for(int i = 1; i < n; i++){
            if(map[s[i-1]] > map[s[i]]) return false;
        }
        return true;
    }
};


//用two pointer解 time: o(n) space: o(1)
class Solution1{
public:
    bool isSubsequence(string s, string t) {
        int n = s.length();
        int m = t.length();
        int i =0, j = 0;
        while(i < n && j < m){  //兩個string 只要有一個到頭了就結束啦
            if(s[i] == t[j]){
                i++;
            }
            j++;   //兩個string指標都會慢慢遞增 所以不會有順序錯誤的問題
        }
        return i==n ? 1:0; //看看是不是string s裡的字元都有在t中找到
    }
};

//用recursion解
class Solution2{
public:
    bool isSubsequence(string s, string t) {
        int n = s.length();
        int m = t.length();
        return isSubseq(s,t, n, m);
    }
    bool isSubseq(string s, string t, int n, int m){
        if(n==0) return true;
        if(m==0) return false; //代表我string t都掃過一遍了還是找不完stirng s的字元
        if(s[n] == t[m]){
            return isSubseq(s,t, n-1, m-1);
        }
        return isSubseq(s,t, n, m-1);
    }
};


int main(){
    string s = "aaaaaa";
    string t ="bbaaaa";
    string c ="ag";
    string d = "abcdefg";
    Solution1 a;
    cout << a.isSubsequence(s,t)<<endl;
    Solution2 b;
    cout << b.isSubsequence(c,d);

    
}

//solution 2 的複雜度解析
/*
时间复杂度：
递归函数的时间复杂度取决于递归的深度和每次递归中的操作复杂度。在这里，每次递归的操作都是常数时间复杂度（比较s[n]和t[m]），
并且递归的深度为n，其中n是字符串s的长度。因为每次递归中，n减小1，所以递归的总操作次数为n。因此，递归函数isSubseq的时间复杂度为O(n)。

空间复杂度：
递归函数的空间复杂度取决于递归的深度，因为每次递归都会在stack中分配一些空间。在这里，由于递归的深度最多为n，其中n是字符串s的长度，
所以递归函数的空间复杂度为O(n)。
*/