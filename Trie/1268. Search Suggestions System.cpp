/*
1268. Search Suggestions System
*/

// TC: O(n * m + k * 26*m) m為建立trie時的平均字串長度 k為搜尋單詞的長度 SC:O(n * m + k * 26)
class Solution {
    class TrieNode{
    public:
        TrieNode(): children(26,NULL), isEnd(0){}
        ~TrieNode(){
            for(auto child : children){
                if(child) delete child;
            }
        }
        vector<TrieNode*> children;
        bool isEnd;
    };
    TrieNode* root;

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        // contruct Trie 
        root = new TrieNode();
        for(const auto &str : products){
            TrieNode* node = root;
            for(const auto &ch:str){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a']  = new TrieNode();
                node = node->children[ch-'a'];
            }
            node -> isEnd = true;
        }

        vector<vector<string>> res;
        TrieNode* node = root;
        string pre;
        for(int i = 0; i < searchWord.size(); i++){
            char ch =  searchWord[i];
            //找不到的情況
            vector<string> ret;
            if(node->children[ch - 'a'] == NULL){
                for(int j = i; j < searchWord.size(); j++){
                    res.push_back({});
                }
                break;
            }
            //找得到情況
            node = node -> children[ch-'a'];
            pre.push_back(ch);

            string str; //用來存遍歷過程
            DFS(node, str, ret);
            for(int j = 0; j < ret.size(); j++){
                ret[j] = pre + ret[j];
            }
            res.push_back(ret);
        }

        return res;
    }
    void DFS(TrieNode* node, string& str, vector<string>& ret){
        if(ret.size() == 3) return;
        if(node -> isEnd == true){
            ret.push_back(str);
        }
        //Trie + DFS的作法 逐個遍歷
        for(int i = 0; i < 26; i++){
            if(node -> children[i] == NULL) continue;
            str.push_back(i + 'a');
            DFS(node->children[i], str, ret);
            str.pop_back();
        }
    }
};

// Sort + Binary Search TC:O(nlgn) SC:O(k)  k為搜尋單詞的長度
class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());

        vector<vector<string>> res;
        string pre;
        
        for(int i = 0; i < searchWord.size(); i++){
            pre.push_back(searchWord[i]);
            vector<string> ret;
            auto iter = lower_bound(products.begin(), products.end(), pre);
            for(int k = 0; k < 3; k++){
                int len = pre.size();
                if(iter == products.end()) break;
                if(iter->substr(0,len) != pre) break;
                ret.push_back(*iter);
                iter = next(iter,1);
            }
            res.push_back(ret);
        }

        return res;
    }
};


/*
此題模擬了googel 自動補字的系統
要你輸出三個跟目前輸入字串相同的字串
1. Trie + DFS 為了要搜索目前符合的前綴之後的單詞 必須寫一個DFS從最小搜到最大字母 每搜到一個在繼續往下遞迴
2. Sort + Binary Search 因為這題給的字典樹單詞沒有到很多 所以可以先sort 然後每次要找某段字的時候都二元搜索
如果找到了還要再確定他是否有符合其前綴

時間複雜度：
建立 Trie： 對於每個產品的每個字符，都要進行 Trie 操作。如果 n 是產品的總數，每個產品的平均長度是 m，建立 Trie 的時間複雜度是 O(n * m)。
搜尋建議詞： 對於每個搜尋字串中的字符，都需要進行 Trie 操作和 DFS。如果搜尋字串的平均長度是 k，搜尋建議詞的時間複雜度是 O(k * 26^k)，因為對於每個字符，最多有 26 個可能的子節點。
總的時間複雜度是 O(n * m + k * 26^k)。

空間複雜度：
Trie 結構： Trie 的空間複雜度主要取決於 Trie 的節點數量。在最壞的情況下，每個產品的每個字符都需要一個 Trie 節點，所以 Trie 的空間複雜度是 O(n * m)。
DFS 遞歸： DFS 遞歸的深度最多是搜尋字串的長度 k，每一層的節點數量是 26。因此，DFS 遞歸的空間複雜度是 O(k * 26)。
總的空間複雜度是 O(n * m + k * 26)。
*/
