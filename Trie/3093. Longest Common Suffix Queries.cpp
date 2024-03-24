/*
3093. Longest Common Suffix Queries
*/

// TC:O(n+m) SC:O(m*26) m 為 wordContainer總字數 n為 wordQuery的總字數
class Solution {
    struct TrieNode{
        TrieNode* children[26];
        int index;
         TrieNode()
        {
            for (int i=0; i<26; i++)
                children[i] = NULL;
            index = -1;
        }        
        
        ~TrieNode(){
            for(auto child : children){
                if(child) delete child;
            }
        }
    };
    TrieNode* root = new TrieNode();
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        
        
        vector<pair<string,int>> arr;
        for(int i = 0; i < wordsContainer.size(); i++){
            arr.push_back({wordsContainer[i],i});
        }
        auto cmp = [](const pair<string,int>& a, const pair<string,int>& b){
          if(a.first.size() != b.first.size()) return a.first.size() < b.first.size();
            else return a.second < b.second;
        };
        
        sort(arr.begin(), arr.end(), cmp);
        
        for(int i = 0; i < arr.size(); i++){
            string s = arr[i].first;
            TrieNode* node = root;
            for(int j = s.size()-1; j >= 0; j--){
                if(node->children[s[j]-'a'] == NULL){
                    node->children[s[j]-'a'] = new TrieNode();
                    node->children[s[j]-'a']->index = arr[i].second;
                } 
                node = node->children[s[j]-'a'];
            }
           
        }
        
        vector<int> res(wordsQuery.size(),-1);
        for(int i = 0; i < wordsQuery.size(); i++){
            string s = wordsQuery[i];
            TrieNode* node = root;
            int idxx = -1;
            for(int j = s.size()-1; j >= 0; j--){
                if(node->children[s[j]-'a']){
                    idxx = node->children[s[j]-'a']->index;
                    node = node->children[s[j]-'a'];
                }
                else break;
                
            }
            
            res[i] = idxx;
            
            if(res[i] == -1) res[i] = arr[0].second;
        }
        
        return res;
    }
};

/*
找最長共同後綴
Constraints:

1 <= wordsContainer.length, wordsQuery.length <= 104
1 <= wordsContainer[i].length <= 5 * 103
1 <= wordsQuery[i].length <= 5 * 103
wordsContainer[i] consists only of lowercase English letters.
wordsQuery[i] consists only of lowercase English letters.
Sum of wordsContainer[i].length is at most 5 * 105.
Sum of wordsQuery[i].length is at most 5 * 105.
 因為給的限制很明顯不能暴力搜索 要有效率搜索字串就會想到1.kmp 2. trie 這題不是求前後綴類型 所以會是trie
給定的wordContainer不會超過5*10^5 即使*26也會剛好 所以會用trie
接下來比較聰明的做法是將wordContainer按字串長度排序 如果一樣長那就是按照index排序 這樣就能先將長度較小的符合題目要求的優先賦予index
*/
