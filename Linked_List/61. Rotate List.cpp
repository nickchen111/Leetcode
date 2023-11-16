/*
61. Rotate List
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        //將倒數k+1個斷開並且重新跟頭連接
        if(head == NULL || head->next == NULL) return head;
        ListNode* dummy = new ListNode(-1);
        dummy->next=head;
        int count = 0;
        ListNode* p = dummy;
        while(p->next != NULL){
            count+=1;
            p = p->next;
        }

        k%=count;
        if(k == 0) return head;
        ListNode* q = dummy;
        for(int i=0; i<count-k; i++){
            q = q->next;
        }
       
        //q現在指向要斷開的點上
        ListNode* h = q->next;
        q->next = NULL;
        p->next = head;

        return h;
    }
};
