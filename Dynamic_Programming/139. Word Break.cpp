/*
139. Word Break
*/

// 2025.02.28 Hash Set 逆著存 + 劃分型DP TC:O(mL + n*L) m = wordDcit 長度, L為最長字串長度, n 為 string s長度
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


//dfs+trie 在更優化就是加上memorization   tc:O(n^2) sc:O(n^2)
class Solution {
    struct TrieNode{//這是一種寫法 也可以寫成class
        TrieNode(){
            isEnd = false;
            for(int i = 0; i<26; i++){
                children.push_back(nullptr);
            }
        }
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }
        vector<TrieNode*> children;
        bool isEnd;
    };
    int memo[300];
    TrieNode* root;

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        root = new TrieNode();
        
        //構建trie
        for(auto word:wordDict){

            TrieNode* p = root;

            for(auto ch: word){
                if(p->children[ch - 'a'] == nullptr){
                    p->children[ch - 'a'] = new TrieNode();
                }
                p = p->children[ch-'a'];
            }
            p->isEnd = true;
        }
        //分割string s 傳入 並確認他的後面是否也可以被分割 此題只需確認是否可分割 
        return backtrack(s, 0);

    }
    bool backtrack(string& s, int cur){
        
        
        if(cur == s.size()) return true; //代表走到尾了都可以切割 
        if(memo[cur] == -1) return false;//之前就走過是不行的

        TrieNode* p = root;
        for(int i = cur; i < s.size(); i++){
            if(p->children[s[i] - 'a'] != nullptr){
                p = p->children[s[i] - 'a'];
                if(p->isEnd == true && backtrack(s, i+1)) return true;
            }
            else break;
        }

        memo[cur] = -1;
        return false;
    }
};


//dp解 tc: O(n*m*k) sc:  O(n + m)
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
