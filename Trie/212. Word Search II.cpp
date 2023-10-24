/*
212. Word Search II
*/

//Trie + DFS  TC:O(m*n*4^L + W*L) SC:O(W*L+m*n+L) W:單詞的數量 L:單詞的平均長度
class Solution {
    struct TrieNode{
        TrieNode(): isEnd(0), children(26, nullptr){}
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }

        vector<TrieNode*> children;
        bool isEnd;
    };
    TrieNode* root;
    int m, n;
    vector<bool> visited;
    unordered_set<string> ans;//去重 可能會有重複的字詞
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size(); n = board[0].size();

        root = new TrieNode();
        //建立字典樹
        for(auto word:words){
            TrieNode* node = root;
            for(auto ch:word){
                if(node->children[ch-'a'] == nullptr) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
            }
            node->isEnd = true;
        }

        //開始搜尋
        visited = vector<bool>(m*n+1);

       for(int i = 0; i<m; i++){
           for(int j = 0; j<n; j++){
               string word;
               TrieNode* node = root;
               visited[i*n+j] = true;
               DFS(board, i, j, word, node);
               visited[i*n+j] = false;
           }
       }

       vector<string> res(ans.begin(),ans.end());

       return res;
    }

    vector<int> dirs = {0,1,0,-1,0};
    void DFS(vector<vector<char>>& board, int i, int j, string& word, TrieNode* node){
        //base case
        if(node->children[board[i][j]-'a'] == nullptr) return;
        node =node->children[board[i][j]-'a'];
        word.push_back(board[i][j]);

        if(node->isEnd == true){
            ans.insert(word);//不return 因為可能後續還有前綴一樣的單詞

        }

        for(int k = 1; k<dirs.size(); k++){
            int nx = i + dirs[k-1];
            int ny = j + dirs[k];
            if(nx<0 || ny<0 || nx>=m || ny>=n || visited[nx*n+ny] == true) continue;
            visited[nx*n+ny] = true;
            DFS(board,nx,ny,word,node);
            visited[nx*n+ny] = false;
        }
        word.pop_back();//走回去之後還需要把word裡面的字詞pop掉
    }
};

//Trie+DFS+ count剪枝 TC:O(m*n*4^L + W*L) SC:O(W*L+m*n+L) W:單詞的數量 L:單詞的平均長度
class Solution {
    struct TrieNode{
        TrieNode(): isEnd(0), children(26, nullptr), count(0){}
        ~TrieNode(){
            for(auto child:children){
                if(child) delete child;
            }
        }

        int count;
        vector<TrieNode*> children;
        bool isEnd;
    };
    TrieNode* root;
    int m, n;
    vector<bool> visited;
    unordered_set<string> ans;//去重 可能會有重複的字詞
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size(); n = board[0].size();

        root = new TrieNode();
        //建立字典樹
        for(auto word:words){
            TrieNode* node = root;
            for(auto ch:word){
                if(node->children[ch-'a'] == nullptr) node->children[ch-'a'] = new TrieNode();
                node = node->children[ch-'a'];
                node->count +=1;
            }
            node->isEnd = true;
        }

        //開始搜尋
        visited = vector<bool>(m*n+1);

       for(int i = 0; i<m; i++){
           for(int j = 0; j<n; j++){
               string word;
               TrieNode* node = root;
               visited[i*n+j] = true;
               DFS(board, i, j, word, node);
               visited[i*n+j] = false;
           }
       }

       vector<string> res(ans.begin(),ans.end());

       return res;
    }

    vector<int> dirs = {0,1,0,-1,0};
    void DFS(vector<vector<char>>& board, int i, int j, string& word, TrieNode* node){
        //base case
        if(node->children[board[i][j]-'a'] == nullptr) return;
        if(node->children[board[i][j]-'a']->count == 0) return;
        node =node->children[board[i][j]-'a'];
        word.push_back(board[i][j]);

        if(node->isEnd == true){
            ans.insert(word);//不return 因為可能後續還有前綴一樣的單詞
            remove(root,word);
            node->isEnd = false;

        }

        for(int k = 1; k<dirs.size(); k++){
            int nx = i + dirs[k-1];
            int ny = j + dirs[k];
            if(nx<0 || ny<0 || nx>=m || ny>=n || visited[nx*n+ny] == true) continue;
            visited[nx*n+ny] = true;
            DFS(board,nx,ny,word,node);
            visited[nx*n+ny] = false;
        }
        word.pop_back();//走回去之後還需要把word裡面的字詞pop掉
    }

    void remove(TrieNode* root, string& word){
        TrieNode* node = root;
        for(auto ch:word){
            node = node->children[ch-'a'];
            node->count -=1;
        }
    }
};


/*
此題不僅僅是要搜尋一個單詞 還有可能會搜尋好多個前綴一樣或者重複的單詞
需用字典樹處理提高效率
考點：
1.想到用trie來高效搜索
2.去掉重複搜尋到的字詞
3.考慮到一直不斷搜索相同字串的狀況如何避免
*/
