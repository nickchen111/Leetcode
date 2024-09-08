/*
725. Split Linked List in Parts
*/

// TC:O(n) SC:O(n)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    int count = 0;
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        ListNode* n = head;
        DFS(n);
        int mod = count % k; // 3
        int num = count/k; // 0

        vector<ListNode*> res;
        ListNode* p = head;
        for(int i = 0; i < k; i++){
            int cnt = (mod > 0) + num;
            mod --;
            res.push_back(p);
            for(int j = 0; j < cnt-1; j++){
                head = head -> next;
            }
            ListNode* tmp = head;
            if(tmp) {
                head = head -> next;
                tmp -> next = NULL;
            }
            p = head;
        }

       

        return res;

    }
    void DFS(ListNode* node){
        if(node == NULL) return;
        count += 1;
        DFS(node->next);
    }
};
