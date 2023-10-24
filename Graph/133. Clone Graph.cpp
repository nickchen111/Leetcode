/*
133. Clone Graph
*/

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


//此題是給你一個利用上面的結構連結出的節點graph 要你複製出一個一模一樣的graph結點圖 
//分兩部分做 先建立結點在做連結
//用dfs做
class Solution1 { //先建點在做連結(undirected) 用dfs
public:
    unordered_map<Node*, Node*> map;
    Node* cloneGraph(Node* node) {
        if(node == nullptr) return nullptr;

        Node* newnode = new Node(node->val);
        map[node] = newnode;

        for(auto nextnode:node->neighbors){
            if(map.find(nextnode) != map.end()){
                newnode->neighbors.push_back(map[nextnode]);
            }
            else newnode->neighbors.push_back(cloneGraph(nextnode)); //代表還沒有這點去遞迴加入他進hash table
        }
        return newnode;

    }
};


//bfs
class Solution2 { 
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> map;
        queue<Node*> q;
        if(node == nullptr) return nullptr;
        q.push(node);
        map[node] = new Node(node->val);

        while(!q.empty()){
            Node* root = q.front();
            q.pop();
    
            for(int j = 0; j < root->neighbors.size(); j++){
                if(map.find(root->neighbors[j]) == map.end()){
                    map[root->neighbors[j]] = new Node(root->neighbors[j]->val); //找不到就去新增他
                    map[root]->neighbors.push_back(map[root->neighbors[j]]);//確立跟root為鄰居
                    q.push(root->neighbors[j]);//放入q中之後查他鄰居
                }
                else map[root]->neighbors.push_back(map[root->neighbors[j]]);//之前已經查過他鄰居惹 不用再加入q
            }
        }
        return map[node];
    }
};
