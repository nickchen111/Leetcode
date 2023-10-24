/*
143. Reorder List
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* p = dummy;
        //計算總共有幾個節點
        int count = 0;
        while(p != NULL){
            count++;
            p = p->next;
        }
        //找到要斷開的點
        ListNode* q = dummy;
        for(int i = 0; i < (count+1)/2; i++){
            q = q->next;
        }

        //斷開並且記錄要反轉的那段的頭
        ListNode* head2 = q->next;
        q->next = NULL;
        //翻轉後面那段
        head2 = reverseN(head2);

        
        p = head; q = head2;
        ListNode* h = dummy;
        while(p || q){
            if(p){
                h->next = p;
                p = p->next;
                h = h->next;
            }
            if(q){
                h->next = q;
                q = q->next;
                h = h->next;
            }
        }
        
    }

    ListNode* reverseN(ListNode* head){
        ListNode* prev = NULL;
        ListNode* cur = head;
        ListNode* nxt;
        while(cur){
            nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }

        return prev;
    }
};
