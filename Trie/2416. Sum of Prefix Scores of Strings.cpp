/*
2416. Sum of Prefix Scores of Strings
*/

// TC:O(n*L) L為單詞平均長度 SC:O(n*L)
class Solution {
    struct TrieNode{
    TrieNode* children[26];
    int count;
    bool isValid;
        TrieNode(){
            for(int i = 0; i < 26; i++){
                children[i] = NULL;
            }
            count = 0;
            isValid = 0;
        }
        ~TrieNode(){
            for(auto child : children){
                if(child) delete child;
            }
        }
    };
    TrieNode* root;
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        root = new TrieNode();
        for(auto &word : words){
            TrieNode* node = root;
            for(auto &ch : word){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
                node->count += 1;
            }
            node->isValid = 1;
        }

        vector<int> res;
        unordered_set<string> set;
        for(auto &word : words){
            int sum = 0;
            TrieNode* node = root;
            for(auto &ch : word){
                if(node->children[ch-'a'] != NULL) node = node->children[ch-'a'];
                sum += (node->count);
            }
            res.push_back(sum);
        }

        return res;
    }
};

/*
給了一串字串數組 問說他們能組出的前綴 數組內有幾個字串剛好也有相同的前綴
用數組的形式回答每一個字串有可能的前綴在數組中有幾個
Trie -> count 每一個字被走過了幾次
*/
