/*
127. Word Ladder
*/


//BFS TC:O(n*26*l) n為wordlist數量 l為單詞的字數 SC:O(n)
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //此題只需要計算最短路徑為多長
        //先將每個字的可能性coding出來
        unordered_map<string, vector<string>> next;
        wordList.push_back(beginWord);
        unordered_set<string> wordSet(wordList.begin(), wordList.end());

        for(auto s:wordSet){
            for(int i = 0; i<s.size(); i++){
                for(auto ch = 'a'; ch<='z'; ch++){
                    string t = s;
                    if(ch == s[i]) continue;
                    t[i] = ch;
                    if(wordSet.find(t) != wordSet.end()){
                        next[s].push_back(t);
                    }
                }
            }
        }

        queue<string> q;
        q.push(beginWord);
        unordered_set<string> visited;
        visited.insert(beginWord);
        int res = 1;
        while(!q.empty()){
            int sz = q.size();
            res++;
            for(int i = 0; i<sz; i++){
                string cur = q.front();
                q.pop();
                for(auto nextWord:next[cur]){
                    if(visited.find(nextWord) != visited.end()) continue;
                    visited.insert(nextWord);
                    q.push(nextWord);
                    if(nextWord == endWord) return res;
                }
            }
        }

        return 0;
    }
};
