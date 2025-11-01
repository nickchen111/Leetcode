/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        unordered_set<int> set(nums.begin(), nums.end());

        while(head != NULL){
            if(set.find(head->val) == set.end()){
                p->next = new ListNode(head->val);
                p = p->next;
            }
            head = head -> next;
        }
        
        return dummy -> next;
    }
};