/*
2707. Extra Characters in a String
*/

// 2025.03.01 Hash Set + DP TC:O(n * L) SC:O(mL + n) L 為字串最大長度 m為字典中的字串數量
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        unordered_set<string> set;
        int max_len = 0;
        for(auto str : dictionary) {
            max_len = max(max_len, (int)str.size());
            reverse(str.begin(), str.end());
            set.insert(str);
        }
        vector<int> dp(n+1, INT_MAX/2);
        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            string tmp;
            for(int j = i - 1; j >= max(i - max_len, 0); j--) {
                tmp += s[j];
                if(set.count(tmp)) {
                    dp[i] = min(dp[i], dp[j]);
                }
                else {
                    dp[i] = min(dp[i], dp[j] + i - j);
                }
            }
        }
        return dp[n];
        /*
        遞歸 TC:O(n * L) SC:O(mL + n) L 為字串最大長度 m為字典中的字串數量
        vector<int> memo(n, INT_MAX);
        auto dfs = [&](auto &&dfs, int i) -> int {
            if(i < 0) return 0;
            int &ret = memo[i];
            if(ret != INT_MAX) return ret;
            string tmp;
            for(int j = i; j >= 0; j--) {
                tmp += s[j];
                if(set.count(tmp)) {
                    ret = min(ret, dfs(dfs, j-1));
                }
                else ret = min(ret, dfs(dfs, j-1) + i - j + 1);
            }
            return memo[i] = ret;
        };
        return dfs(dfs, n - 1);
        */
    }
};
 
// DP + Trie: TC:O(n^2 +  m*L) SC:O(n + m*L)
class Solution {
    struct TrieNode {
        TrieNode* next[26];
        bool isEnd;
        TrieNode() {
            for(int i = 0; i < 26; i++) next[i] = NULL;
            isEnd = false;
        }
    };
    TrieNode* root = new TrieNode();
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        for(auto &str : dictionary) {
            TrieNode* node = root;
            for(auto &ch : str) {
                if(node->next[ch - 'a'] == NULL) node->next[ch - 'a'] = new TrieNode();
                node = node->next[ch - 'a'];
            }
            node -> isEnd = true;
        }
        vector<int> dp(n+1, 0);
        for(int i = n-1; i >= 0; i--) {
            dp[i] = dp[i+1] + 1; // 不選
            TrieNode* node = root;
            for(int j = i; j < n; j++) {
                if(node -> next[s[j] - 'a'] != NULL) {
                    node = node -> next[s[j] - 'a'];
                    if(node -> isEnd) {
                        dp[i] = min(dp[i], dp[j+1]);
                    }
                }
                else break;
            }
        }
        return dp[0];
        
        /*
        遞歸 TC:O(n^2 + mL) SC:O(n + mL)
        vector<int> memo(n, INT_MAX/2);
        auto dfs = [&](auto &&dfs, int i) -> int {
            if (i == n) return 0;
            int &ret = memo[i];
            TrieNode* node = root;
            if(ret != INT_MAX/2) return ret;
            ret = min(ret, 1 + dfs(dfs, i+1)); // 不選
            for(int j = i; j < n; j++) {
                if(node->next[s[j] - 'a'] != NULL) {
                    node = node->next[s[j] - 'a'];
                    if(node -> isEnd) {
                        ret = min(ret, dfs(dfs, j + 1));
                    }
                }
                else {
                    ret = min(ret, dfs(dfs, j+1) + j - i + 1);
                    break;
                }
            }
            return ret;
        };
        
        return dfs(dfs, 0);
        */
    }
};
