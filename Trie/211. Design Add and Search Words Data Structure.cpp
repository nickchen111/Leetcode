/*
211. Design Add and Search Words Data Structure
此題為基本題的變形 多了限制條件如果word給妳.要當成符合條件
因此這裡更改了find的返回值 以及傳入的argument數目 多了 TrieNode* node. int index
改成用dfs遞迴的方式逐一檢查如果遇到. 其後續的點遇到.下一個word能否順利判斷完且 is_word要是true 

"tc: o(26^k) sc: o(N*26)
其中 k 是搜索的單詞長度，26 是字母表的大小。
其中 N 是插入的總單詞數量，26 是字母表的大小。"
*/

class WordDictionary {
private:
    struct TrieNode{
        TrieNode(): is_word(false), children(26, nullptr){};

        ~TrieNode(){
            for(TrieNode* child:children){
                if(child) delete child;
            }
        }
        bool is_word;
        vector<TrieNode*> children;
    };

    std::unique_ptr<TrieNode> root;

    //為了要解這題 用dfs的方式去解.的這種情況 用dfs 去recursion
    // 這個私有函數是為了用DFS方式處理模糊搜索
    bool find(const string& word, TrieNode* node, int index){
        if(node == nullptr) return false;
        if(index == word.length()) return node->is_word; // 判斷是否為完整的單詞

        if(word[index] == '.'){
            for(TrieNode* temp:node->children){
                if(find(word, temp, index+1)){//看後面是否順利，不順會是 false，當下就會返回
                    return true;
                }
            }
        }

        //這種情況下是字母
        else{
            int tempindex = word[index] - 'a';
            TrieNode* temp = node->children[tempindex];

            return find(word, temp, index+1);
        }

        return false;//就會變到這return false
    }

public:
    WordDictionary(): root(new TrieNode()) {
        //初始化root
    }
    
    void addWord(string word) {
        TrieNode* p = root.get();
        for(const char c:word){
            if(!p->children[c - 'a']) p->children[c - 'a'] = new TrieNode();
            p = p->children[c - 'a'];
        }
        p->is_word = true;
    }
    
    bool search(string word) {
        TrieNode* p = root.get();
        return find(word, p, 0);
    }
};
