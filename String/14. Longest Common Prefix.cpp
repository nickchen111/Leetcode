/*
14. Longest Common Prefix
*/


//Trie TC:O(n*k) n為字串數量 k為字串平均長度 SC:O(n*k)如果字串都不一樣
class Solution {
    struct TrieNode{
        TrieNode(): isEnd(0), children(26,NULL),count(0){};
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }
        bool isEnd;
        vector<TrieNode*> children;
        int count;
    };
    TrieNode* root;
public:
    string longestCommonPrefix(vector<string>& strs) {
        root = new TrieNode();

        //遍歷時間就是m*n
        for(auto str:strs){
            TrieNode* node = root;
            for(auto ch:str){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
                node->count+=1;
            }
            node->isEnd = true;
        }

        string res = "";
        int len = 0;
        int target = strs.size();
        TrieNode* node = root;
        for(auto str:strs){
            for(auto ch:str){
               if(node->children[ch-'a'] != NULL && node->children[ch-'a']->count == target){
                   res.push_back(ch);
                   node = node->children[ch-'a'];
               }
            }
            break;//做一次就好哩
        }

        return res;
    }
};

//TC:O(n*m) SC:O(1)
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res = "";
        for(int i = 0; i<strs[0].size(); i++){
            for(int j = 1; j <strs.size(); j++){
                if(strs[0][i] != strs[j][i]) return res;
            }
            res+=strs[0][i];
        }

        return res;
    }
};
