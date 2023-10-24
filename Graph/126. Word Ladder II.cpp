/*
126. Word Ladder II
*/


// BFS TC:O(n*26^l) n為wordlist數量 l為單詞的字數 SC:O(n + k*l) k為路徑數量
class Solution {
    unordered_map<string, vector<string>> prev;//紀錄可行路上之前的字有哪些
    string beginWord;
    vector<vector<string>> res;
    
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //想求從一開始的字走到最後的字 每次只能調一個字 的最短走法有哪些-->BFS
        unordered_map<string, vector<string>> next;//紀錄每個字後續的可能性
        this->beginWord = beginWord;

        wordList.insert(wordList.begin(),beginWord);
        unordered_set<string> wordSet(wordList.begin(),wordList.end());//去重
        //開始構建每個字能走到的字有哪些 鄰接表
        for(auto s:wordSet){
            for(int i = 0; i<s.size(); i++){
                for(auto ch='a'; ch<='z'; ch++){
                    string t = s;
                    if(s[i] == ch) continue;
                    t[i] = ch;
                    if(wordSet.find(t) != wordSet.end())
                        next[s].push_back(t);
                }
            }
        }

        //開始遍歷看能怎麼走
        queue<string> q;
        q.push(beginWord);
        unordered_set<string> visited({beginWord});
        int flag = 0;
        while(!q.empty()){
            int sz = q.size();
            unordered_set<string> newVisited;
            for(int i = 0; i<sz; i++){
                string cur = q.front();
                q.pop();
                for(auto nextword:next[cur]){
                    if(visited.find(nextword) != visited.end()) continue;
                    newVisited.insert(nextword);
                    prev[nextword].push_back(cur);//去紀錄走法 一但發現達到最終點要從這擷取正確做法
                    
                    if(nextword == endWord) flag = 1;//這裡還不能停 可能有其他跟他同層的也可以走到
                }
            }
            //這裡再將新加入的加入visited 如果在上面就加入 可能導致 終點抵達後 只有一組會被accept 其他都因為走過了無法加入
            for(auto x:newVisited){
                visited.insert(x);
                q.push(x);
            }
            if(flag == 1) break;
        }

        vector<string> path({endWord});
        DFS(endWord,path);

        return res;
    }
    //這裡不能用& 會改變到他的順序
    void DFS(string curWord, vector<string> path){
        if(curWord == beginWord){
            reverse(path.begin(),path.end());
            res.push_back(path);
            return;
        }

        for(auto prevWord:prev[curWord]){
            path.push_back(prevWord);
            DFS(prevWord, path);
            path.pop_back();
        }
    }
};
