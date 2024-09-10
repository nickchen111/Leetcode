/*
2807. Insert Greatest Common Divisors in Linked List
*/

// TC:O(n * log(max(a,b))) SC:O(n)
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
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        if(head == NULL) return NULL;
        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        while(head -> next){
            int x = head -> val;
            int y = head -> next -> val;
            int num = GCD(x,y);
            ListNode* p = head -> next;
            head->next = new ListNode(num);
            head->next->next = p;
            head = head->next->next;
        }
        
        return dummy -> next;
    }
    int GCD(int x, int y){
        // 125 25
        while(y > 0){
            int t = x % y;
            x = y;
            y = t;
        }

        return x;
    }
};
