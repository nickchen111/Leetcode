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
 
// DP + Trie: TC:O(n^2 +  M*L) SC:O(n + M*L) L為字串數量 M為平均長度
class Solution {
    class TrieNode{
    public:
        TrieNode():children(26,NULL), isValid(0){}
        ~TrieNode(){
            for(auto &child : children){
                if(child) delete child;
            }
        } 
        vector<TrieNode*> children; 
        bool isValid;
    };

    TrieNode* root;
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        
        root = new TrieNode();
        for(auto &word : dictionary){
            TrieNode* node = root;
            for(auto &ch : word){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isValid = true;
        }

        vector<int> dp(n+1, 0);
        
        
        for(int i = n-1; i >= 0; i--){
            dp[i] = dp[i+1] + 1;//這點去除的狀況下
            TrieNode* node = root;
            for(int j = i; j < n; j++){
                if(node->children[s[j] - 'a'] != NULL){
                    node = node->children[s[j] - 'a'];
                    if(node->isValid == true){
                        dp[i] = min(dp[i], dp[j+1]);
                    }
                }

                else break;
            }
        }

        return dp[0];
    }
};
