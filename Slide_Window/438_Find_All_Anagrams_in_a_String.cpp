/*
438. Find All Anagrams in a String
*/


#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


//slide window tc: o(n) sc:o(k)
//與567題很像 只是改成要求索引位置罷了
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int left = 0, right = 0;
        int valid = 0;
        unordered_map<char, int> need, window;
        vector<int> ans;
        for(char c:p){
            need[c]++;
        }

        //開始套模
        while(right < s.size()){
            char a = s[right];
            right++;

            if(need.count(a)){
                window[a]++;
                if(window[a] == need[a]){
                    valid++;
                }
            }

            while(right - left >= p.size()){
                // 当窗口符合条件时，把起始索引加入 ans
                if(valid == need.size()){//這裡去更新答案
                    ans.push_back(left);
                }

                char d = s[left];
                left++;

                if(need.count(d)){
                    if(window[d] == need[d]){
                        valid--;
                    }
                    window[d]--;
                }
            }
        }

        return ans;
    }
};
/*
此題是想問說如果一字串中包含一個字串的異位詞anagram 請返回他的起始索引位置
仍然是需要一個valid 去紀錄ok的結果 跟need 紀錄需要什麼
1.用模板先想出何時該擴大何時該縮小
2.什麼位置可以將答案更新
*/