/*
82. Remove Duplicates from Sorted List II
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //此題為83題的follow up 要將重複的完全移除 不留任何一個
        if(head == NULL || head->next == NULL) return head;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* p = dummy;
        
        //每次都是兩個數值在做比較
        while(p->next != NULL && p->next->next != NULL){
            //就算跳出回圈了 他的下一個值也可能是重複
            if(p->next->val  == p->next->next->val){
                int val = p->next->val;
                while(p->next != NULL && p->next->val == val) p->next = p->next->next;
            }
            else {
               p = p->next;
            }
        }

        return dummy->next;
    }
};
