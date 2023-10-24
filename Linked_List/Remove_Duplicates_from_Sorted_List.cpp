/*
83. Remove Duplicates from Sorted List
*/

#include <iostream>
#include <unordered_map>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//此題想將linked list 去重 返回去好的list 
//  雙指針技巧去重 for linked list tc: o(n) sc: o(1)
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



//la大
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode* slow = head;  // 当前元素
    ListNode* fast = head;  // 下一个元素
    while (fast != nullptr) {
        if (fast->val != slow->val) {
            // 当前元素的下一个元素设置为下一个不相等的元素
            slow->next = fast;
            // 当前元素向后移动
            slow = slow->next;
        }
        // 下一个元素向后移动
        fast = fast->next;
    }
    // 断开与后面重复元素的连接
    slow->next = nullptr;
    return head;
}