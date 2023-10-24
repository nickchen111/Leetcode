/*
141. Linked List Cycle
*/



//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

 
// 基礎的linked list判斷有無cycle問題 tc: o(n) sc:o(1)
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode * slow = head;
        ListNode * fast = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if(fast == slow) return true;
        }
        return false;

    }
};

/*
解題思維：
判斷linked list有無cycle的基本題型
1.創建slow fast雙指針
2. slo 每次走一步 fast 走兩步 當兩個指針遇到的時候就代表有cycle
3.停止條件為fast 走到null or 他的下一個不存在
*/
