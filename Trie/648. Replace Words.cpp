/*
648. Replace Words
*/
class Solution {
    class Trie{
    private:
        struct TrieNode{
            TrieNode(): is_word(false), children(26, nullptr){}
            ~TrieNode(){
                for(TrieNode* child:children){
                    if(child) delete child;
                }
            }

            bool is_word;
            vector<TrieNode*> children;
        };

        std::unique_ptr<TrieNode> root;//指向struct TrieNode
    
    public:
        Trie(): root(new TrieNode()){};
        
        void insert(string word){
            TrieNode* p = root.get();
            for(const char c:word){
                if(p->children[c-'a'] ==nullptr) p->children[c-'a'] = new TrieNode();
                p = p->children[c - 'a'];
            }
            p->is_word = true;
        }
        string replace(string& word){
            string result;
            string str;
            TrieNode* node = root.get();
            dfs(node, word, 0, str, result);
            if(result != "") return result;
            else return word;
        }
        void dfs(TrieNode* node, string& word, int k, string str, string& result){

            if(node->is_word == 1){
                result = str;
                return;
            }

            if(k == word.size()) return; //代表沒有此前綴符合is_word = true;

            
            if(node->children[word[k] - 'a']){
                str+=word[k];
                return dfs(node->children[word[k]-'a'], word, k+1, str, result);
            }
            
        }
    };    

public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        Trie f;
        for(int i = 0; i < dictionary.size(); i++){
            f.insert(dictionary[i]);//每次的插入都是o(k) 
        }

        int i = 0;//怕第一個字就是空
        while(i < sentence.size() && sentence[i] == ' ') i++;

        string result;
        while(i < sentence.size()){
            int i0 = i;
            while(i < sentence.size() && sentence[i] != ' ') i++;
            string str = sentence.substr(i0, i-i0);
            string str2 = f.replace(str);
            result +=str2;
            result += " ";
            i++;
        }
        result.pop_back(); //去掉最後一個空格
        return result;
    }
};

/*
解題思路：
此題為trie考題 要求最短的前綴 並且把字串改為其前綴 字串處理上要多處理空格的狀況
此題不僅僅是要寫出trie的模板 
還要在主函式裡去設計
1. 加入字詞
2. 將sentence分割並且去判斷是否需要做replace
tc: o(nk + Vk) 是不是k也要乘上V之類的 因為sentence裡可能會有個 V個單詞
sc: o(26*nk) + o(Vk)
*/

/*
构建 Trie 的時間複雜度：假設單詞的平均長度為 k，插入每個單詞到 Trie 中的時間複雜度為 O(k)。如果有 n 個單詞，則插入所有單詞的時間複雜度為 O(nk)。
DFS 搜索的時間複雜度：在最壞的情況下，我們需要遍歷 Trie 中的所有分支。由於 Trie 中的分支數量是固定的（26 個字母），DFS 的時間複雜度在 Trie 的高度上是線性的，即 O(k)。
總體時間複雜度：O(nk) + O(k)，其中 n 是單詞數量，k 是單詞的平均長度。

空間複雜度方面，主要在於 Trie 的空間佔用和遞迴調用的堆棧空間。Trie 的空間佔用在於存儲每個字符的節點，空間複雜度為 O(26 * nk)，
其中 n 是單詞數量，k 是單詞的平均長度。遞迴調用的堆棧空間在 DFS 過程中被使用，取決於 Trie 的高度，即 O(k)。因此，總體空間複雜度是 O(26 * nk) + O(k)
*/
