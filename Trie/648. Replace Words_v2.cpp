/*
648. Replace Words
*/

//不用dfs 根據題目先在主函式做兩件事 1. 加入字典樹 2.拆解string 當遇到空格  接著創建一個單獨的函式去分析是否有完整前綴可取代
class Solution {
    struct TrieNode{
        TrieNode(): isEnd(false), children(26, nullptr){}
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }
        bool isEnd;
        vector<TrieNode*> children;
    };
    TrieNode* root;


    string replace(string& word){
        //去遍歷看看究竟你是要換還是不用換
        TrieNode* node = root;
        for(int i = 0; i < word.size(); i++){
            if(node->children[word[i]-'a'] != nullptr){
                node = node->children[word[i]-'a'];
                if(node->isEnd == true) return word.substr(0, i+1);
            }
            else return word;
        }
        return word;
    }
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        root = new TrieNode();
        //構造trie
        for(auto word:dictionary){
            TrieNode* node = root;
            for(auto ch:word){
                if(node->children[ch-'a'] == nullptr) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isEnd = true;
        }


        string res;//解答 隨時準備更新
        int i = 0;
        while(i < sentence.size() && sentence[i] == ' ') i++; //只是為了防止第一個字是空格

       
        while(i < sentence.size()){
            int i0 = i; //把字首記起來
            while(i < sentence.size() && sentence[i] != ' ') i++;
                
            string str = sentence.substr(i0, i-i0);
            string str2 = replace(str);
            res+=str2;
            res+= ' ';
            i++;
        }
        res.pop_back();

        return res;
    }
};

/*
if word -> isEnd -> replace it  
if not -> keep same
這題因為要拆解字串所以要把比較的工作另外分出去一個函式去做 不然好難拆
tc: O(n* M) sc: O(N*M+L) 
L 表示字典中所有单词字符的总数 n為字串總長度
单词数量 N，以及单词的平均长度 M
*/
