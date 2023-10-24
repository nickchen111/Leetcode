/*
208. Implement Trie (Prefix Tree)
Trie 經典模板
*/

class Trie {
private:
    struct TrieNode{
        TrieNode(): is_word(false), children(26, nullptr){};//初始化 也可以寫成另一種型式
        ~TrieNode(){
            for(TrieNode* child:children){
                if(child) delete child;
            }
        }

        bool is_word;
        vector<TrieNode*> children;
    };
    std::unique_ptr<TrieNode> root;//會自動釋放記憶體的智能指针

    // 寫一個給search startwith用的find函式
    TrieNode* find(const string& word){
        TrieNode* p = root.get();//.get()用以獲取指向所管理对象的原始裸指针
        for(const char c:word){
            p = p->children[c - 'a'];
            if(p == nullptr) break;
        }
        return p;
    }
public:
    Trie(): root(new TrieNode()){
    //初始化root
    }
    
    void insert(string word) {
        TrieNode* p = root.get();
        for(const char c:word){
            if(!p->children[c - 'a']) p->children[c - 'a'] = new TrieNode();
            p = p->children[c - 'a'];
        }
        p->is_word = true;
    }
    
    //找一個string是否完整存在
    bool search(string word) {
        TrieNode *p = find(word);

        return p && p->is_word; //需要加p 是因為怕p是 nullptr會有空指針錯誤
    }
    
    bool startsWith(string prefix) {
        TrieNode* p = find(prefix);

        return p != nullptr; //find(prefix) != nullptr;這樣寫更簡潔
    }
};

/*
tc: o(K) sc: o(N*M) 設N為插入的單詞數量，M為平均單詞長度。
*/
