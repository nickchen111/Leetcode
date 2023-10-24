/*
116. Populating Next Right Pointers in Each Node
*/


class Solution {
public:
    Node* connect(Node* root) {
        if(root == nullptr) return nullptr;
        traverse(root->left, root->right);

        return root;
    }
    void traverse(Node* node1, Node* node2){
        if(node1 == nullptr || node2 == nullptr) return;

        //將傳入的兩個節點串起來
        node1->next = node2;

        //將同父節點的node連接起來
        traverse(node1->left, node1->right);
        traverse(node2->left, node2->right);
        //將不同父節點的node連接起來
        traverse(node1->right, node2->left);
    }
};

/*
解題思路：
此題想將所有節點去指向他右邊的節點 可以用traverse遍歷的方式去解

传统的 traverse 函数是遍历二叉树的所有节点，但现在我们想遍历的其实是两个相邻节点之间的「空隙」。
现在，我们只要实现一个 traverse 函数来遍历这棵三叉树，每个「三叉树节点」需要做的事就是把自己内部的两个二叉树节点穿起来
tc: o(n) sc: o(lgn)
*/
