/*
3043. Find the Length of the Longest Common Prefix
*/

// TC:O(m*n) SC:O(26*m) m = len of word , n = number of word
class Solution {
    struct TrieNode{
        TrieNode(){
            isEnd = false;
            for(int i = 0; i<10; i++){
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
    TrieNode* root;
    int res = 0;
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        vector<string> s1;
        vector<string> s2;
        root = new TrieNode();
        for(auto c : arr1){
            s1.push_back(to_string(c));
        }
        for(auto c : arr2){
            s2.push_back(to_string(c));
        }
        
        for(int i = 0; i < s1.size(); i++){
            TrieNode* node = root;
            for(auto ch : s1[i]){
                if(node->children[ch-'0'] == NULL) node->children[ch-'0'] = new TrieNode();
                node = node->children[ch-'0'];
            }
            node->isEnd = 1;
        }
        
        for(int i = 0; i < s2.size(); i++){
            TrieNode* node = root;
            DFS(s2[i], 0, node, 0);
        }
        
        return res;
    }
    
    void DFS(string& s, int count, TrieNode* node, int i){
        if(i == s.size()){
            res = max(res, count);
            return;
        }
        res = max(res, count);
        if(node->children[s[i]-'0'] == NULL) return;
        
        node = node->children[s[i]-'0'];
        DFS(s, count+1, node, i+1);
    }
};

/*
找出兩個字串數組的LCP 取最長的大小即可
因為這題數具規模給定兩個字串都是5*10^4 不能一個一個去比較 要想到prefix求前綴 前面可能很多重複的狀況 所以將其中一個數組轉成字典樹
在用另外一個數組去遍歷看最多可以到多長 這樣時間就會壓在 5*10^4*10 級別
*/
