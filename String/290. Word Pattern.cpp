/*
290. Word Pattern
*/

// TC:O(m+n) SC:O(m+n)
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        //先將string s切割
        vector<string> words;
        string str = "";
        for(int i = 0; i<s.size(); i++){
            if(s[i] == ' '){
                words.push_back(str);
                str = "";
            }
            else str+=s[i];
        }
        words.push_back(str);
        //先確認是否數量一致
        if(pattern.size() != words.size()) return false;
        //開始做映射
        unordered_map<char,string> map;
        unordered_set<string> set;//紀錄這個字是否出現過 
        for(int i = 0; i<pattern.size(); i++){
            //之前用這個單字映射過了但這次映射後的字不同
            if(map.find(pattern[i]) != map.end()){
                if(map[pattern[i]] != words[i]) return false;
            }
            //這個單字沒用過 但是要映射的字之前出現過了 
            else if(set.find(words[i]) != set.end()) return false;
            map[pattern[i]] = words[i];
            set.insert(words[i]);
        }
        return true;
    }
};
