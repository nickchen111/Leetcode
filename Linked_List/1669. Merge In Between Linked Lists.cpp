/*
1669. Merge In Between Linked Lists
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = list1;
        ListNode* p1 = dummy;
        //走到要連接的第二段與第一段前面
        ListNode* p2 = dummy;
        for(int i = 0; i < a; i++){
            p1 = p1->next;
        }
        for(int i = 0; i < b+2; i++){
            p2 = p2->next;
        }
        ListNode* p3 = list2;
        while(p3->next != NULL) p3 = p3->next;
        p1->next = list2;
        p3->next = p2;

        return dummy->next;
    }
};
