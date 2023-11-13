/*
24. Swap Nodes in Pairs
*/

// Recursion TC:O(n) SC:O(n/2)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //Recursion
        if(head == NULL || head->next == NULL) return head;
        ListNode* first = head;
        ListNode* second = head->next;
        ListNode* other = swapPairs(head->next->next);
        first->next = other;
        second->next = first;

        return second;
    }
};

// Iterative TC:O(n) SC:O(n/2)
class Solution {
    bool flag = 1;
public:
    ListNode* swapPairs(ListNode* head) {
        //跟25題可以一樣做法
        vector<ListNode*> heads;
        if(head == NULL || head->next == NULL) return head;

        ListNode* p = head;
        while(p){
            heads.push_back(p);
            for(int i = 0; i<1; i++){
                if(p->next) p = p->next;
                else flag = 0;
            }
            ListNode* tmp = p->next;
            p->next = NULL;
            p = tmp;
        }

        for(int i = 0; i<heads.size(); i++){
            if(flag == 0 && i == heads.size()-1) continue;
            heads[i] = reverseN(heads[i]);
        }

        for(int i=0; i<heads.size()-1; i++){
            ListNode* cur = heads[i];
            while(cur->next != NULL){
                cur = cur->next;
            }
            cur->next = heads[i+1];
        }

        return heads[0];
    }

    ListNode* reverseN(ListNode* node){
        ListNode* prev = NULL;
        ListNode* cur = node;
        ListNode* nxt;
        while(cur != NULL){
            nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        return prev;
    }
};
