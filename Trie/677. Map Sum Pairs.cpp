/*
677. Map Sum Pairs
*/

class MapSum {
    //trie寫法 如果前綴字很多空間複雜度可以下降很多
private:
    struct TrieNode{
        TrieNode(): sum(0), children(26, nullptr){};
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }
        int sum;
        vector<TrieNode*> children;
    };
    std::unique_ptr<TrieNode> root;
    unordered_map<string, int> key2val;
public:
    MapSum(): root(new TrieNode()) {
        
    }
    
    void insert(string key, int val) {
        int inc = val - key2val[key];//如果有重複字串被加入的情況
        TrieNode* p = root.get();
        for(auto c:key){
            if(!p->children[c-'a']){
                p->children[c-'a'] = new TrieNode();
            }
            p->children[c-'a']->sum +=inc;
            p = p->children[c-'a'];
        }
        key2val[key] = val;
    }
    
    int sum(string prefix) {
        TrieNode* p = root.get();
        for(auto c:prefix){
            if(p->children[c-'a'] == nullptr) return 0;
            p = p->children[c-'a'];
        }
        return p->sum;
    }
};


class MapSum {
    //兩個hash table寫法 key太長就很浪費空間 不用trie結構
private:
    unordered_map<string, int> key2val;
    unordered_map<string, int> key2sum;
public:
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        int inc = val;
        if(key2val.count(key)){
            inc -=key2val[key];
        }
        key2val[key] = val;
        for(int i = 1; i <= key.size(); i++){
            key2sum[key.substr(0,i)] +=inc; //代表每個char 都會有一個對應的sum 空間複雜度高
        }

    }
    
    int sum(string prefix) {
        return key2sum[prefix];
    }
};


 /*
 解題思路：
 
 1.設計map的insert結構
 2.設計一個找前綴的 如果沒有直接返回0 
   有的話就去dfs 直到nullptr 看經過的is_word 帶的數字 加總起來->太慢了
   在insert的時候就開始累加sum 之後直接看有無前綴 到指定前綴的尾巴字元確認sum是多少即可
 */
