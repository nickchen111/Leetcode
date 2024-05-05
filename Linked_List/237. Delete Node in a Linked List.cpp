/*
237. Delete Node in a Linked List
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    void deleteNode(ListNode* node) {
        auto next = node->next;
        *node = *next;
        delete next;
    }
};
