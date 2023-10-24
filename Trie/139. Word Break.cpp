/*
139. Word Break
*/

//Trie+backtrack+memorization tc:O(n^2) sc:O(n^2)
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

//暴力解
class Solution {
    //brute force -> backtrack 
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


//dp
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
/*
時間複雜度：
外層循環遍歷了 n 次，其中 n 是輸入字符串 s 的長度。
內層循環遍歷了 wordDict 中的每個單詞，最壞情況下可能需要遍歷 wordDict 的所有單詞，假設 wordDict 中有 m 個單詞。
在內層循環中，執行了 substr 和比較操作，這些操作的時間複雜度取決於單詞的平均長度。
總的時間複雜度是 O(n * m * k)，其中 k 是 wordDict 中單詞的平均長度。在最壞情況下，當 wordDict 中的所有單詞都需要比較時，這個解法的時間複雜度可能會較高。

空間複雜度：
使用了一個大小為 n+1 的 dp 數組，用於存儲中間結果，這將消耗 O(n) 的額外空間。
除了 dp 數組之外，額外的空間消耗主要來自輸入參數 wordDict 的大小，即 m 個單詞。
*/

/*
解題思路：
1. backtrack每種可能暴力解 
時間複雜度超高 o(n^n) 空間上可以用hash map來降低一些時間複雜度

2. backtrack + trie 來讓搜索效率提升 且空間上也比較省 +memo剪枝

3. dp
dp[i] s[第幾個字符為止是合法的]
*/
