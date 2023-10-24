/*
344. Reverse String
*/


#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size()-1;

        while(left < right){
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
};

/*
此題概念即reverse()函式的實作
用雙指針的左右指針方式
*/