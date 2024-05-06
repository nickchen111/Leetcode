/*
2487. Remove Nodes From Linked List
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
       
        ListNode* dummy = new ListNode(INT_MAX);
        
        vector<ListNode*> arr;
        arr.push_back(dummy);

        for(ListNode* i = head; i != NULL; i = i->next){
            while(arr.back()->val < i->val){
                arr.pop_back();
            }
            arr.back()->next = i;
            arr.push_back(i);
        }
       
        

        return dummy->next;
    }
};
