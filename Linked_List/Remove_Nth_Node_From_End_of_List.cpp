/*
19. Remove Nth Node From End of List
*/


#include <iostream>
#include <queue>
using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


// 此題是想讓你將一串linked list裡面的倒數第n個元素給刪掉
//tc: o(n) sc:o(1)
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1); //創造虛擬頭節點以防極端情況
        ListNode* p = head;
        dummy->next = p;//也可以指向head
        ListNode* x = findFromEnd(dummy, n+1); //找尋倒數第k+1個
        x->next = x->next->next;//跳過第k個元素
        
        return dummy->next;

    }
    ListNode* findFromEnd(ListNode* head, int k){// 此項很重要！！！要能找出倒數第k個元素在哪 by 雙指針
        ListNode* p1 = head;
        ListNode* p2 = head;
        for(int i=0; i<k; i++){//p1先走k步
            p1 = p1->next;
        }

        while(p1 != nullptr){//p1走完剩下步數(n-k)with p2
            p1 = p1->next;
            p2 = p2->next;
        }
        return p2;
    }
};

/*
解題思路
1.首先這題必定要有雙指針linked list中 可以同步搜尋到倒數第k個元素的函式
2.利用此函式求出倒數第k+1的元素
3.將此元素連結的位址改為第k個的下一個去跳過他
ps:注意極端情況 如果只有一個元素的話該怎麼辦
*/