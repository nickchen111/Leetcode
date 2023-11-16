/*
109. Convert Sorted List to Binary Search Tree
*/

// Divide and Conquer TC:O(n) SC:O(lgn)
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(head == NULL) return NULL;
        return DivideConquer(head,NULL);
    }
    TreeNode* DivideConquer(ListNode* start, ListNode* end){
        if(start == end) return NULL;
        //找出中間那項
        ListNode* slow = start;
        ListNode* fast = start;
        while(fast != end && fast->next != end){
            fast = fast->next->next;
            slow = slow->next;
        }
        TreeNode* root = new TreeNode(slow->val);
        root->left = DivideConquer(start,slow);
        root->right = DivideConquer(slow->next,end);
        return root;
    }
};

// Recursion TC:O(n) SC:O(lgn)
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        //reursion
        if(head == NULL) return NULL;
        if(head->next == NULL){
            TreeNode* root = new TreeNode(head->val);
            return root;
        }
        //因為只有兩個點以下的情況快慢指針也無法前進
        if(head->next->next == NULL){
            TreeNode* root = new TreeNode(head->val);
            root->right = new TreeNode(head->next->val);
            return root;
        }

        ListNode* slow =head;
        ListNode* fast =head;
        ListNode* tmp;
        while(fast != NULL && fast->next != NULL){
            tmp=slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        TreeNode* root = new TreeNode(slow->val);
        tmp->next = NULL;
        root->left = sortedListToBST(head);
        root->right = sortedListToBST(slow->next);
        return root;
    }
};

/*
-10 -3 0 5 9 NULL

*/
