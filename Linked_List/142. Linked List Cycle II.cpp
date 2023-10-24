/*
142. Linked List Cycle II
*/

//TC:O(n+k) SC:O(1)
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;

        while(fast && fast->next){//判斷有無環
            fast = fast->next->next;
            slow = slow->next;
            if(fast==slow) break;
        }
        //判斷出圈理由
        if(fast == nullptr || fast->next == nullptr) return nullptr; //沒環

        slow = head;// slow重新指回head

        while(slow != fast){ //兩個一起走k-m步就會是環的起點哩
            slow = slow->next;
            fast = fast->next;
        }

        return slow;
    }
};


/*
此題也可使用hash table判斷有無重複 
解題思路：
判斷linked list有無環的進階題 還要判斷還的起點
1. 先用基本套路去看這個有沒有環 沒還直接return nullptr 
2. 判斷出回圈的原因是因為有環還是因為沒環
3.有環的話 再創一個slow 去指向head 走到slow = fast就是環的起點
*/

//hash table tc: o(n) sc: o(n)
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        int i=0;
        unordered_map<ListNode*,int> m;
        ListNode*temp=head;
        while(temp!=NULL){
            if(m.find(temp)!=m.end()) return temp;
            m[temp]=i++;
            temp=temp->next;
        }  
        return NULL;
    }
};
