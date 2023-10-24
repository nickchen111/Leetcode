/*
208. Implement Trie (Prefix Tree)
*/

//這個模板時間上更高效
class Trie {
    struct TrieNode{
        TrieNode(): isEnd(0), children(26, nullptr){}
        ~TrieNode(){
            for(auto child: children){
                if(child) delete child;
            }
        }
        vector<TrieNode*> children;
        bool isEnd;
    };
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();    
    }
    
    void insert(string word) {
        TrieNode* node = root;
        for(auto ch:word){
            if(node->children[ch-'a'] == nullptr) node->children[ch-'a'] = new TrieNode();
            node = node->children[ch-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for(auto ch:word){
            if(node->children[ch-'a'] != nullptr){
                node = node->children[ch-'a'];
            }
            else return false;
        }
        return node->isEnd  == true;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for(auto ch:prefix){
            if(node->children[ch-'a'] != nullptr){
                node = node->children[ch-'a'];
            }
            else return false;
        }
        return true;
    }
};
