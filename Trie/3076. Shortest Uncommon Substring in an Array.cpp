/*
3076. Shortest Uncommon Substring in an Array
*/


// Trie TC:O(n*m*m*m) n = 100, m = 20 -> 8e5, SC:O(26*20)
class Solution {
    struct TrieNode{
        vector<TrieNode*> children;
        int count;
        TrieNode(): children(26,NULL), count(0){}  
    };
    TrieNode* root = new TrieNode();
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        
        int n =  arr.size();
        vector<string> res(n);
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < arr[i].size(); j++){
                TrieNode* node = root;
                for(int k = j; k < arr[i].size(); k++){
                    if(node->children[arr[i][k]-'a'] == NULL) node->children[arr[i][k]-'a'] = new TrieNode();
                    node = node->children[arr[i][k]-'a'];
                    node->count += 1;
                }
            }
        }
        
        for(int i = 0; i < n; i++){
            string ret = "";
            for (int j = 0; j < arr[i].size(); j++)
            {
                TrieNode* node = root;
                for (int k = j; k < arr[i].size(); k++)
                {
                    node = node->children[arr[i][k]-'a'];
                    node->count--;                                                     
                }                
            }
            
            for(int len = 1; len <= 20; len++){
                for(int j = 0; j + len -1 < arr[i].size(); j++){
                    string cur = arr[i].substr(j,len);
                    TrieNode* node = root;
                    if(check(cur,node) && (ret == ""  || (cur.size() == ret.size() && cur < ret))){
                        ret = cur;
                    }
                }
                if(ret.size() > 0) break;
            }
            
            res[i] = ret;
            
            for (int j = 0; j < arr[i].size(); j++)
            {
                TrieNode* node = root;
                for (int k = j; k < arr[i].size(); k++)
                {
                    node = node->children[arr[i][k]-'a'];
                    node->count++;                                                     
                }                
            }
            
        }
        
        return res;
    }
    bool check(string& s, TrieNode* node){
    
        for(int i = 0; i < s.size(); i++){
            if(node->children[s[i]-'a']->count == 0){
               return true;  
            } 
            
            node = node->children[s[i]-'a'];
        }
        
        return false;
    }
};

// Hash Map TC:O(n*m*m*m) n = 100, m = 20 -> 8e5, SC:O(4e6)
class Solution {
public:
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n =  arr.size();
        unordered_map<string, int> map;
        vector<string> res(n);
        for(int i = 0; i < n; i++){
            for(int len = 1; len <= 20; len++){
                for(int j = 0; j + len - 1 < arr[i].size(); j++){
                    string cur = arr[i].substr(j,len);
                    map[cur] += 1;
                }
            }
        }
        
        for(int i = 0; i < n; i++){
            string ret = "";
            for(int len = 1; len <= 20; len++){
                for(int j = 0; j + len -1 < arr[i].size(); j++){
                    string cur = arr[i].substr(j,len);
                    map[cur] -= 1;
                }
                for(int j = 0; j + len -1 < arr[i].size(); j++){
                    string cur = arr[i].substr(j,len);
                    if((ret == "" || cur.size() < ret.size() || (cur.size() == ret.size() && cur < ret)) && map[cur] == 0){
                        ret = cur;
                    }
                    map[cur] += 1;
                }
            }
            res[i] = ret;
        }
        
        return res;
        
    }
};

/*
找到string數組中每個string的substring他會是其他string沒有出現過的最短substring 並要求字典序最小

trie + DFS or Hash Map 
長度 1~20 取出去看看是否沒有存在
比賽時我覺得空間夠所以就用hash map 空間 : 存的每一個字串平均長度10 100個字串 每一個最多都可以存20*20個字串進去 40000*10 = 4e6
賽後復盤了Trie的做法 他需要再看每一個字串的時候對他做刪減 檢查 再新增
*/
