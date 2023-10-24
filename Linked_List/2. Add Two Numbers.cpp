/*
2. Add Two Numbers
*/

// TC:O(max(m,n)) SC:O(max(m,n))
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        ListNode* p1=l1;
        ListNode* p2=l2;
        //有最後一個數加起來超過10的可能 此時循環也不能停 要進位
        int carry = 0;
        while(p1 != NULL || p2 != NULL || carry){
            int val = carry;//搞不好之前有進位 在這先assign
            if(p1 != NULL){
                val+=p1->val;
                p1 = p1->next;
            }
            if(p2 != NULL){
                val+=p2->val;
                p2 = p2->next;
            }

            //開始處理進位 以及list答案建立操作
            carry = val/10;//是否進位
            val = val%10;//求個位數
            p->next = new ListNode(val);
            p = p->next;
        }

        return dummy->next;
    }
};

//code簡短的寫法 感覺精美
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        //有最後一個數加起來超過10的可能 此時循環也不能停 要進位
        int carry = 0;
        //code短小的寫法
        while(l1 || l2 || carry){
            carry+=(l1 ? l1->val:0) + (l2 ? l2->val:0);
            l2 = l2 ? l2->next:NULL;
            l1 = l1 ? l1->next:NULL;

            p->next = new ListNode(carry%10);
            carry/=10;
            p = p->next;
        }

        return dummy->next;
    }
};
