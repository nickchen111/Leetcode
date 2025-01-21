// Sliding Window TC:O(n*m^2) m = 10 SC:O(L) L為所有字串的數字量
class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int n = word.size();
        unordered_set<string> set(forbidden.begin(), forbidden.end());
        int i = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            for(int k = j; k >= max(j - 10, i); k--) {
                if(set.count(word.substr(k, j - k + 1))) {
                    i = k + 1;
                    break;
                }
            }
            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};

// Trie TC:O(n*m) m = 10 SC:O(L) L為所有字串的數字量
class Solution {
    struct TrieNode {
        bool isEnd;
        TrieNode* next[26];
        TrieNode() {
            for(int i = 0; i < 26; i++) {
                next[i] = NULL;
            }
            isEnd = false;
        }
    };
    TrieNode* root = new TrieNode();
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int n = word.size();
        // unordered_set<string> set(forbidden.begin(), forbidden.end());
        for(auto &s : forbidden) {
            TrieNode* node = root;
            for(int i = s.size()-1; i >= 0; i--) {
                if(node->next[s[i]-'a'] == NULL ) node->next[s[i]-'a'] = new TrieNode();
                node = node->next[s[i]-'a'];
            }
            node -> isEnd = true;
        }
        int i = 0, ans = 0;
        // 如何用Trie優化時間 緩存不友善指針
        for(int j = 0; j < n; j++) {
            TrieNode* node = root;
            for(int k = j; k >= max(j - 10, i); k--) {
                if(node->next[word[k]-'a'] == NULL) break;
                else {
                    node = node->next[word[k]-'a'];
                    if(node -> isEnd) {
                        i = k + 1;
                        break;
                    }
                }
            }
            ans = max(ans, j - i + 1);
        }

        return ans;
    }
};

/*
今天要選出來的最長子串 不包含任何禁忌的字串
禁忌的字串 <= 10
*/
