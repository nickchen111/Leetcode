/*
3295. Report Spam Message
*/

// TC:O(n*bannedWords平均長度) SC:O(m*bannedWords平均長度)  m = bannedWords.size()
class Solution {
public:
    bool reportSpam(vector<string>& message, vector<string>& bannedWords) {
        unordered_set<string> set;
        for(auto word : bannedWords){
            set.insert(word);
        }
        
        int count = 0;
        for(auto word : message){
            if(set.find(word) != set.end()) count += 1;
            if(count == 2) return true;
        }
        return false;
    }
};
