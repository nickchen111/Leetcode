/*
2707. Extra Characters in a String
*/
 
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


// DP + Hash Set TC:O(n^3 + M*L) L為字串數量 M為平均長度 SC:O(n + M*L)
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size();
        int maxVal = n+1;
        vector<int> dp(n+1, maxVal);//一個不可能到達的數字
        dp[0] = 0;

        unordered_set<string> set(dictionary.begin(), dictionary.end());

        for(int i = 1; i <= n; i++){
            dp[i] = dp[i-1] + 1;//這點去除的狀況下
            for(int j = 1; j <= i; j++){
                if(set.find(s.substr(i-j,j)) != set.end()){
                    dp[i] = min(dp[i], dp[i-j]);
                }
            }
        }

        return dp[n];
    }
};

/*
將一串字串去字典樹找有無相應的字 盡量讓剩下的字串越少越好 最少可以剩下幾個字
50*50*50*50 6e6
leetscode -> leets leet code
1. Trie+DFS : 每走一步都要從頭確認 會超時 且代碼難寫
dp[i] 從[1:i] 需要去除的最少字母量 
2. Hash set : TC:O(n^3 + M*L) L為字串數量 M為平均長度
3. 用trie的話要反過來寫 正著寫會不曉得j會涵蓋到哪裡 只知道要取他前面那串的最小值 但不曉得他有沒有包含了i
x x x j x x x i
*/
