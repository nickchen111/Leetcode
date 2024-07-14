/*
3217. Delete Nodes From Linked List Present in Array
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> set(nums.begin(), nums.end());
        
        ListNode* dummy = new ListNode(-1);
        ListNode* p = new ListNode(-1);
        p->next = head;
        dummy->next = p;
        while(p->next != NULL){
            if(set.find(p->next->val) == set.end()){
                p = p->next;
            }
            else {
                p->next = p->next->next;
            }
        }
        
        return dummy->next->next;
    }
};
