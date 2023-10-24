/*
557. Reverse Words in a String III
Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and 
initial word order.

Example 1: 
Input: s = "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"

Example 2:
Input: s = "God Ding"
Output: "doG gniD"
*/


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


//two pointer 自己想出來的解答 可以再寫得更簡潔一點 如solution1
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int i = 0;
        int j = 0;
        while(j < n){
            if(s[j] !=' '){
                j++;
            }
            if(s[j] ==' ' || s[j] == '\0'){
                reverse(&s[i], &s[j]);
                i = j+1;
                j++;
            }
        }
        return s;
    }
};


//solution 1 
class Solution1 {
public:
    string reverseWords(string s) {
        int n = s.length();
        int i = 0;
        int j = 0;
        for(j = 0; j < n; j++){
            if(s[j] ==' '){
                reverse(s.begin()+ i, s.begin()+ j);
                i = j+1;
            }
        }
            reverse(s.begin()+ i, s.end());
        
        return s;
    }
};
/*
时间复杂度：
for循环遍历字符串s的时间复杂度为O(n)，其中n是字符串s的长度。
reverse()函数的时间复杂度为O(m)，其中m是每个单词的平均长度。在这里，m的大小不会超过n，因为每个单词都不会超过字符串s的长度。
总共有n个单词，因此所有reverse()函数的调用的时间复杂度为O(n * m)。
综合起来，Solution1的时间复杂度为O(n^2)。

空间复杂度：
Solution1的空间复杂度是O(1)，因为它只使用了常数级别的额外空间来存储临时变量。*/



//用streamstring 跟getline： split & reverse
class Solution2 {
public:
    // customize split function
    vector<string> split(string s, char deli){
        stringstream str(s);
        string line;
        vector<string> response;
        while(getline(str, line, deli)){
            response.push_back(line);
        }
        return response;
    }

    string reverseWords(string s) {
        // split by ' '
        vector<string> v = split(s, ' ');
        // reverse each string
        for(auto &x : v) reverse(x.begin(), x.end());
        // construct the answer
        string ans;
        for(int i = 0; i < v.size(); i++) {
            ans += v[i];
            // add space after each string except the last one
            if(i != v.size() - 1) ans += " ";
        } 
        return ans;
    }
};

/*
时间复杂度：
split()函数的时间复杂度为O(n)，其中n是字符串s的长度。split()函数需要遍历整个字符串s来查找分隔符' '。
对每个单词调用reverse()函数的时间复杂度为O(m)，其中m是每个单词的平均长度。在这里，m的大小不会超过n，因为每个单词都不会超过字符串s的长度。
两个for循环遍历v的时间复杂度为O(n)。
综合起来，Solution2的时间复杂度为O(n^2)。

空间复杂度：
split()函数中使用了stringstream和vector，它们分别会使用O(n)和O(n)的额外空间。因此，split()函数的空间复杂度为O(n)。
Solution2中使用了vector<string> v来存储切分后的单词，它会使用O(n)的额外空间。
string ans用于构建结果字符串，它的空间复杂度也是O(n)。
综合起来，Solution2的空间复杂度为O(n)。
*/

int main(){
    string s= "you are a pig";
    Solution1 a;
    Solution2 b;
    cout << a.reverseWords(s) << "\n" << b.reverseWords(s) <<endl;

    return 0;
}