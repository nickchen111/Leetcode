/*
1367. Linked List in Binary Tree
*/

// KMP+DFS TC:O(m+n) SC:O(m+n)
lass Solution {
    vector<int> suf;
    vector<int> list;
    int dp[2500];
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        suf = preprocessor(head);
        return DFS(root,0);
    }

    bool DFS(TreeNode* node, int i){
        if(node == NULL) return false;
        
        if(i == 0) dp[0] = (node->val == list[0]);
        else{
            int j = dp[i-1];
            while(j > 0 && list[j] != node->val){
                j = suf[j-1];
            }
            dp[i] = j + (list[j] == node->val);
        }

        if(dp[i] == list.size()) return true;
    
        return DFS(node->left,i+1) || DFS(node->right,i+1);
    }

    vector<int> preprocessor(ListNode* head){
        while(head != NULL){
            list.push_back(head->val);
            head = head->next;
        }

        int n=list.size();
        vector<int> dp(n,0);
        for(int i =1; i<n; i++){
            int j = dp[i-1];
            while(j > 0 && list[j] != list[i]){
                j = dp[j-1];
            } 
            dp[i] = j+(list[i] == list[j]);
        }

        return dp;
    }
};

// 遞歸解法 TC:O(m*n) SC:O(max(m,n))
class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root) {
        //跟572題很像不過改成LinkedList資料結構並且可以允許只要是subPath就好
        if(root == NULL) return false;
        if(isSamePath(head,root)) return true;

        return isSubPath(head,root->left) || isSubPath(head,root->right);
    }

    bool isSamePath(ListNode* head, TreeNode* root){
        if(head == NULL) return true;
        if(root == NULL) return false;
        if(head->val != root->val) return false;

        return isSamePath(head->next,root->left) || isSamePath(head->next,root->right);
    }
};

/*
跟572題很像不過改成LinkedList資料結構並且可以允許只要是subPath就好
如果要用KMP的解法 那麼此題因為不是比較兩個樹所以不是都一起用前序遍歷來做比較 而是用DFS+KMP來做
*/
