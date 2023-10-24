/*
206. Reverse Linked List
*/

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
// recursion
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;// base case

        ListNode* last = reverseList(head->next); //reverse 函式會返回reverse後的新頭節點
        head->next->next = head; //魔法發生的地方 將當前節點的下一個節點的 next 指針指向當前節點，從而實現反轉的操作
        head->next = nullptr;

        return last;
    }
};

class Solution {
// it te ra ti ve!!!
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return head;

        ListNode* previous = nullptr;
        ListNode* current = head;
        ListNode* preceding = head->next;

        //三指針方式 current會是變換方向的那個
        while(preceding != nullptr){
            current->next = previous;
            previous = current;
            current = preceding;
            preceding = preceding->next;
        }
        current->next = previous;
        head = current;

        return head;
    }
};


/*
解題思維
兩種方式
1. 迭代 tc:o(n) sc:o(1)
2. 遞歸 tc:o(n) sc: o(n)
*/
