/*
139. Word Break
*/

// 2025.02.28 Hash Set 逆著存 + 劃分型DP TC:O(mL + n*L) m = wordDcit 長度, L為最長字串長度, n 為 string s長度 SC:O(mL + n)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //DP
        int n = s.size();
        int max_len = 0;
        unordered_set<string> set;
        for(auto word : wordDict) {
            max_len = max(max_len, (int)word.size());
            reverse(word.begin(), word.end());
            set.insert(word);
        }
        vector<int> dp(n+1);
        dp[0] = true;
        for(int i = 1; i<=n; i++){
            string tmp;
            for(int j = i-1; j >= max(0, i - max_len); j--) {
                tmp += s[j];
                if(set.count(tmp) && dp[j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};

// 2025.02.28 DP + Trie 遞推寫法 TC:O(n^2) SC:O(mL + n)
class Solution {
public:
    struct TrieNode {
        TrieNode() {
            for(int i = 0; i < 26; i++) children[i] = NULL;
            isEnd = false;
        }
        ~TrieNode() {
            for(auto child: children){
                if(child) delete child;
            }
        }
        TrieNode* children[26];
        bool isEnd;
    };
    TrieNode* root;
    bool wordBreak(string s, vector<string>& wordDict) {
        // 建立 Trie
        root = new TrieNode();
        for(auto &word : wordDict) {
            TrieNode* node = root;
            for(auto ch : word) {
                if(node->children[ch-'a'] == nullptr)
                    node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isEnd = true;
        }
        
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[n] = true;  // 空字串可以拆分
        
        // 從後向前遞推
        for (int i = n - 1; i >= 0; i--) {
            TrieNode* node = root;
            // 嘗試從位置 i 向右擴展
            for (int j = i; j < n; j++) {
                if (node->children[s[j]-'a'] == nullptr) break;
                node = node->children[s[j]-'a'];
                if (node->isEnd && dp[j + 1]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[0];
    }
};


// 2025.02.28 DFS + Trie + memo TC:O(n^2) SC:O(n^2)
class Solution {
    struct TrieNode{
        TrieNode() {
            for(int i = 0; i < 26; i++) children[i] = NULL;
            isEnd = false;
        }
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }
        TrieNode* children[26];
        bool isEnd;
    };
    TrieNode* root = new TrieNode();
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        for(auto word:wordDict){
            TrieNode* node = root;
            for(auto ch:word){
                if(node->children[ch-'a'] == NULL) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isEnd = true;
        }
        int n = s.size();
        vector<int> memo(n, -1);
        auto dfs = [&](auto &&dfs, int cur) -> bool {
            if(cur == n) return true;
            if(memo[cur] != -1) return memo[cur];
            TrieNode* node = root;
            for(int i = cur; i < n; i++){
                if(node->children[s[i]-'a']){
                    node = node->children[s[i]-'a'];
                    if(node->isEnd && dfs(dfs, i+1)) return memo[cur] = true;
                }
                else break;
            }

            return memo[cur] = false;
        };

        return dfs(dfs, 0);
    }
};

// DP解 但不用Hash Set 也不用Trie去做優化 TC: O(n*m*k) SC:  O(n + m)
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) 
    {
        int n = s.size();
        
        vector<bool>dp(n+1,0);
        
        dp[0] = true; //什麼字都沒有 但一定要先設一個true才能繼續抉擇下去
        
        for(int i = 1; i<=n; i++){ //建立dp數組 i算是此段substring的尾巴
        //去比較string的某段sub 是否在字典裡 且他前面的dp是有那麼這一段也是有的
            for(auto word:wordDict){
                if(i >= word.size() && s.substr(i-word.size(), word.size()) == word && dp[i-word.size()]){
                    dp[i] = true;
                    break;//重新再找搞不好會重複用到此word
                }
            }
        }
        return dp[n];
    }
};

// 暴力解 
class Solution {
    //brute force -> backtrack tc: O(n^n)
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return wordBreakHelper(s, wordSet, 0);
    }

    bool wordBreakHelper(string s, unordered_set<string>& wordSet, int start) {
        int n = s.size();
        if(start == n) return true;// 已經遞迴到字符串結尾，表示找到一種分割方式

        for(int end = start+1; end<=n; end++){
            string subStr = s.substr(start, end-start);//必須是超過start至少1的數字
            if(wordSet.count(subStr) && wordBreakHelper(s, wordSet, end)) return true;
            // 如果子字符串在字典中並且後面的部分也可以被分割，則返回 true
        }

        return false; //找不到分割方式
    }
};

