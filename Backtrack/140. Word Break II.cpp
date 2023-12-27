/*
140. Word Break II
*/

class Solution {
    struct TrieNode{
        TrieNode(): isEnd(0), children(26, nullptr){}
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child; 
            }
        }
        bool isEnd;
        vector<TrieNode*> children;
    };
    TrieNode* root;
    vector<string> res;
    vector<int> memo;
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        //構造trie
        root = new TrieNode();
        for(auto word:wordDict){
            TrieNode* node = root;
            for(auto ch:word){
                if(node->children[ch-'a'] == nullptr) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isEnd = true;
        }
        int n = s.size();

        vector<string> temp;//紀錄中途可行的word
        memo = vector<int>(n+1,1); //紀錄從此index開頭是否可行


        //dfs 
        DFS(s, temp, 0);
        return res;
    }
    bool DFS(string& s, vector<string>& temp, int cur){
        //字串要成立條件為 前面找到合法字串加上 後面DFS也為合法的狀態
        if(cur == s.size()){
            //將temp答案放進result裡
            string t;
            for(auto word:temp){
                t+=word+" ";
            }
            t.pop_back();
            res.push_back(t);

            return true;
        }

        if(memo[cur] == 0) return false;

        TrieNode* node = root;
        bool flag = false;
        for(int i = cur; i<s.size(); i++){
          //如果這一串有在字典樹 加入到temp -> DFS去看下一段是否也有
          //有的話將flag立為true 這一串開頭到某個i結尾是可行的概念
            if(node->children[s[i]-'a'] != nullptr){
                node = node->children[s[i]-'a'];
                if(node->isEnd == true){
                    temp.push_back(s.substr(cur, i-cur+1));
                    if(DFS(s,temp, i+1))
                        flag = true;
                    temp.pop_back();
                }
            }
            else break;//找不到直接break
        }

        if(flag == false) memo[cur] = 0;
        return flag;
    }
};
