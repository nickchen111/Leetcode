// Trie : TC:O(m * n) m = 字串平均長度 SC:O(k * t) k 為 字串的每一層平均種類, t 為字串最長長度
class Solution {
    struct TrieNode {
        TrieNode* next[26];
        int cnt;
        TrieNode(){
            for(int i = 0; i < 26; i++) {
                next[i] = NULL;
            }
            cnt = 0;
        }
    };
    TrieNode* root = new TrieNode();
public:
    int prefixCount(vector<string>& words, string pref) {
        for(auto &word : words) {
            TrieNode* node = root;
            for(auto &ch : word) {
                if(node->next[ch-'a'] == NULL) node->next[ch-'a'] = new TrieNode();
                node = node->next[ch-'a'];
                node->cnt += 1;
            }
        }
        TrieNode* node = root;
        int res = 0;
        for(auto &ch : pref) {
            if(node->next[ch-'a'] == NULL) return 0;
            node = node->next[ch-'a'];
            res = node->cnt;
        }
        return res;
    }
};
