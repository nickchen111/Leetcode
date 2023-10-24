/*   
297. Serialize and Deserialize Binary Tree
*/

//10/13 BFS+preorder && DFS
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        //BFS
        string res;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            TreeNode* cur = q.front();
            q.pop();
            if(cur == NULL) res+="#,";
            else{
                res+=to_string(cur->val)+",";
                q.push(cur->left);
                q.push(cur->right);
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        //先將string 處理成treenode
        vector<TreeNode*> node;
        for(int i=0; i<data.size(); i++){
            int j = i;
            while(j < data.size() && data[j] != ',') j++;
            //這時候j就指向某逗號
            string str = data.substr(i,j-i);
            if(str == "#") node.push_back(NULL);
            else node.push_back(new TreeNode(stoi(str)));
            i = j;
        }

        //必是一個node連結兩個子node 但如果碰上null就不用走兩步
        int i = 0; int j = 1;
        while(j < node.size()){
            if(node[i] != NULL){
                node[i]->left = node[j];
                node[i]->right = node[j+1];
                j+=2;
            }
            i+=1;
        }
        return node[0];
    }
};

//看到這就好
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        //前序遍歷本身就是遞歸調用來顯示樹的方式
        if(root == NULL) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        //先將string 處理成treenode
        queue<string> node;
        for(int i=0; i<data.size(); i++){
            int j = i;
            while(j < data.size() && data[j] != ',') j++;
            //這時候j就指向某逗號
            string str = data.substr(i,j-i);
            node.push(str);
            i = j;
        }

        //用遞歸的方式還原 Tree
        return DFS(node);
    }

    TreeNode* DFS(queue<string>& q){
        string cur = q.front();
        q.pop();
        if(cur == "#") return NULL;
        TreeNode* root = new TreeNode(stoi(cur));
        TreeNode* left = DFS(q);
        TreeNode* right = DFS(q);
        root->left = left;
        root->right = right;
        return root;
    }
};

//這是剛開始學的用stringstream 也是利用前序的方式在做 from huahua
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);

    }
private:
    void serialize(TreeNode* root, ostringstream& out){
        if(!root){
            out << "# ";//記得加空格
            return;
        } 
        out << root->val <<" "; //out也可以吸收int 會轉成字串
        serialize(root->left, out);
        serialize(root->right, out);
    }
    TreeNode* deserialize(istringstream& in){
        string temp;
        in >> temp; //遇到空白會停住
        if(temp == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(temp));
        //一樣是在前序的位置
        root->left = deserialize(in);
        root->right = deserialize(in);

        return root;
    }
};

//用bfs from Huifeng Guan 
//前面tree轉string 利用q的特性 一層一層轉出去
//後面string 轉tree思考點在於node 是一個一個分開的 所以創一個數組在想說要怎麼把string分割 分好以後也配好每個node的val 然後藉由two pointer可以對到node跟他的subnode
class Codec1 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        string ans;

        while(!q.empty()){
        
                TreeNode* node = q.front();
                q.pop();
                if(node != nullptr) {
                    ans += to_string(node->val)+",";
                    q.push(node->left);
                    q.push(node->right);
                }
                else ans += "#,";
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) { // 第一步要做的事把字符串分割成字符串數組 黏再一起不好做
        vector<TreeNode*> node;
        for(int i = 0; i < data.length(); i++){  //這個寫法的應用可以熟悉一下操作-> two pointer的運作模式
            int j = i;
            while(j < data.length() && data[j] != ','){
                j++;
            }
            string str = data.substr(i,j-i);
            cout << str<<"\t"<<j<<"\t"<<i<<endl;
            if(str == "#") node.push_back(nullptr);
            else node.push_back(new TreeNode(stoi(str))); // str會一直被覆寫成其他str  這邊就把int val給輸入好了 這裡注意stoi只會轉換數字字符 逗號會被忽略
            i = j; //這樣下次循環就是從 j+1開始 因為有i++;
        }

        //這裡開始把 左右接起來 也是用two pointer
        int i = 0, j = 1; 
        while( j < node.size()){
            if(node[i] != nullptr){
                node[i]->left = node[j];
                node[i]->right = node[j+1];
                j+=2;
            }
            i+=1;
        }
        return node[0]; //回傳第一個就好了 根
    }
};

//下一招藉由preorder的性質 得到的結果是唯一能確定一棵樹的性質！
//也就是說是用到binary tree的分解問題技巧
// the first element must be root
//recursively do the subproblem by  calling the second element
class Codec2 {
public:
//遞歸 用preorder特性來做
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == nullptr) return "#";
        return to_string(root->val) +","+ serialize(root->left)+","+serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) { 
        vector<TreeNode*> node;
        for(int i = 0; i<data.size(); i++){
            int j = i;
            while(j < data.size() && data[j] != ','){
                j++;
            }
            string str = data.substr(i, j-i);
            if(str == "#")  node.push_back(nullptr);
            else node.push_back(new TreeNode(stoi(str)));
            i = j;
        }
        return dfs(node, 0);
    }
    //這裡是打算來建立連結left right
    TreeNode* dfs(vector<TreeNode*> node, int cur){ //int cur為一index
        if(node[cur] == nullptr) return nullptr;
        TreeNode* left = dfs(node, cur+1); // 這裡就得到所有在root左邊的點 都連結好了
        int leftsize = getNum(left);
        TreeNode* right = dfs(node, cur+leftsize+1);
        node[cur]->left = left;
        node[cur]->right = right; //這裡就是實際來連結的

        return node[cur];
    }
    int getNum(TreeNode* node){
        if(node == nullptr) return 1;
        else return 1+ getNum(node->left)+getNum(node->right);
    }
};


//用la大方式實作一次 他只有給到serialize
class Codec {
public:
    string SEP = ",";
    string  null = "#";
    // 這種serialize deserialize都有分解問題構造樹的味道
    string serialize(TreeNode* root) {
        string str;
        serialize(root, str);

        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
    void serialize(TreeNode* root, string& str){
        if(root == nullptr){
            str += null + SEP;//無法直接加上“”內的東東
            return;
        }

        //前序遍歷的位置
        str += to_string(root->val) + SEP;
        serialize(root->left, str);
        serialize(root->right, str);
    }
    TreeNode* deserialize(istringstream& in){
        string temp;//去接收string出來

        //前序遍歷的方式前面一定是root 可以藉此把root left right按照順序連結起來～
        //前序位置
        getline(in, temp, ',');
        if(temp == "#") return nullptr;
        
        TreeNode* root = new TreeNode(stoi(temp));
        root->left = deserialize(in);
        root->right = deserialize(in);

        return root;
    }

};
/*
解題思維
serialize
1.用分解問題的形式 以前序遍歷的方式去分解出這棵樹的root left right
2. 注意該做的事情是放在前序位置 以及看你是要用空格來分隔或者逗號 如果用逗號的話就要在deserialize成單獨字串的時候用getline

deserialize
1. 一樣是用分解題的思維去解這題 主體是想說前序排列的數組肯定第一個是root接下來會是左邊的root....右邊
2.以此特性慢慢去構造出整顆樹 
ps:因為這題是給你前序遍歷順序數組＋有用#去代表nullptr 所以可以直接根據前序順序來構造出一棵樹
*/

int main(){
    string data = "1,2,3,4,5,6,7,8";
    Codec1 a;
    a.deserialize(data);
}
