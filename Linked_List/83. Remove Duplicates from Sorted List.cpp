/*
83. Remove Duplicates from Sorted List
*/



//此題想將linked list 去重 返回去好的list 
//  雙指針技巧去重 for linked list TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != nullptr){
            if(slow->val != fast->val){
                slow->next = fast;
                slow = slow->next;
            }
            fast = fast->next;
        }
        slow->next = nullptr; //把後面重複值的連接都斷開
        return head;
    }
};

