/*
3045. Count Prefix and Suffix Pairs II
*/

// Trie + KMP n = 字串數量 m = 每個字串平均長度TC:O(n*(m + m + m))  SC:O(m)
class Solution {
    using LL = long long;
    struct TrieNode{
        vector<TrieNode*> children;
        int count;
        TrieNode():children(26,NULL), count(0){}
        ~TrieNode(){
            for(auto child : children){
                if(child) delete child;
            }
        }
    };
    TrieNode* root = new TrieNode();
public:
    vector<int> preprocessor(string& s){
        int n = s.size();
        vector<int> suffix(n,0);
        suffix[0] = 0;
        for(int i = 1; i<n; i++){
            int j = suffix[i-1];
            while(j > 0 && s[i] != s[j]){
                j = suffix[j-1];
            }
            suffix[i] = j+(s[i] == s[j]);
        }

        return suffix;
    }
    
    long long countPrefixSuffixPairs(vector<string>& words) {
        
        LL res = 0;
        // n = 字串數量 m = 每個字串平均長度 n*(m + m + m) SC:O(m)
        for(int i = words.size()-1; i >= 0; i--){
            res += find(root, words[i]);
            
            vector<int> next = preprocessor(words[i]);
            int n = words[i].size();
            unordered_set<int> set;
            int len = next[n-1];
            while(len != 0){
                set.insert(len);
                len = next[len-1];
            }
            set.insert(n);
            
            add(root, set, words[i]);
        }
        
        return res;
    }
    
    int find(TrieNode* root, string& s){
        TrieNode* node = root;
        for(int i = 0; i < s.size(); i++){
            if(node->children[s[i]-'a'] == NULL) return 0;
            node = node->children[s[i]-'a'];
        }

        return node->count;
    }
    void add(TrieNode* root,unordered_set<int>& set, string& s){
        TrieNode* node = root;
        for(int i = 0; i < s.size(); i++){
            if(node->children[s[i]-'a'] == NULL) node->children[s[i]-'a'] = new TrieNode();
            node = node->children[s[i]-'a'];
            if(set.find(i+1) != set.end()) node->count += 1;
        }
    }
};

/*
KMP 既是前綴又是後綴的概念是？
pa 
papa
找到了第一個的時候就馬上判斷相減是否可以到index 0 如果後面沒有了那也符合條件
找到最後一個在判斷是否可以是對方的後綴
*/
