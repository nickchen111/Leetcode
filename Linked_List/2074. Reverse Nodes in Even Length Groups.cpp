/*
2074. Reverse Nodes in Even Length Groups
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        vector<ListNode*> heads;
        int len = 1;
        vector<int> lens;
        ListNode* p = head;
        bool flag = false;
        while(p != NULL){
            heads.push_back(p);
            int count=1;
            for(int i = 0; i<len-1; i++){
                if(p->next) {
                    p = p->next;
                    count+=1;
                }
                else{
                    flag = true;
                    break;
                }
            }
            lens.push_back(count);
            if(flag) break;
            ListNode* tmp = p->next;
            p->next = NULL;
            p = tmp;
            len+=1;
        }

        for(int i = 0; i<heads.size();i++){
            if(lens[i]%2==0) heads[i] = reverseN(heads[i]);
        }
        for(int i = 0; i<heads.size()-1; i++){
            ListNode* h = heads[i];
            while(h->next != NULL) h = h->next;
            h->next = heads[i+1];
        }

        return heads[0];
    }
    ListNode* reverseN(ListNode* node){
        if(node == NULL || node->next == NULL) return node;
        ListNode* prev=NULL; ListNode* cur = node; ListNode* nxt;
        while(cur != NULL){
            nxt = cur->next;
            cur->next = prev;
            prev=cur;
            cur=nxt;
        }
        return prev;
    }
};
