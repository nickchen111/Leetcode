/*
2816. Double a Number Represented as a Linked List
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* doubleIt(ListNode* head) {
        if (head->val > 4)
            head = new ListNode(0, head);
        for(ListNode* node = head; node; node = node->next) {
            node->val = (node->val * 2) % 10;
            if (node->next && node->next->val > 4)
                node->val++;
        }
        return head;
    }
};


// TC:O(n) SC:O(n)
class Solution {
public:
    ListNode* doubleIt(ListNode* head) {
        string s;
        int len = 0;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* p = head;
        while(p){
            s += (p->val + '0');
            p = p->next;
        }
        int carry = 0;
        int i = s.size()-1;
        while(i >= 0){
            char ch = s[i];
            int num = (ch-'0')*2 + carry;
            carry = num / 10;
            s[i] = (num % 10) +'0';
            i--;
        }
        
        if(carry){
            s.insert(s.begin(),'1');
        }

        i = 0;
        p = dummy;
        
        while(i < s.size()){
            if(p->next == NULL) p->next = new ListNode(-1);
            p->next->val = s[i]-'0';
            p = p->next;
            i++;
        }

        return dummy->next;
    }
};
