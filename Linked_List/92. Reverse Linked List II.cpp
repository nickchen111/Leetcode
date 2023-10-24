/*
92. Reverse Linked List II
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
    //recursion寫法
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left == 1) return reverseN(head, right); //left為１的話就是翻轉前n個node

        //如果left 不是1 那就讓他變為1

        head->next = reverseBetween(head->next, left-1, right-1);
        return head;
    }

    ListNode* successor = nullptr; //用來接反轉後該指向的node
    // revese前n個節點就是多了限制n的 反轉整個linked list 只不過尾巴接的要用successor確認
    ListNode* reverseN(ListNode* head, int n){
        if(n == 1){ //base case
            successor = head->next;
            return head;
        }

        ListNode* last = reverseN(head->next, n-1); //  如果從第二個node開始當作第一個 那就是翻轉n-1個
        head->next->next = head;//reverse
        //每次回圈中都會先接上最後的反轉點的下一個node 10/11
        head->next = successor; //接上該接的沒有被翻轉node起始點 

        return last;
    }
};

class Solution {
    //iterative
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode* p = dummy;// 指針

        for(int i = 0; i < right; i++){// 開始分三部分 斷開右邊區間
            p = p->next;
        }
        ListNode* c = p->next;//c為右邊區間的頭
        p->next = nullptr;

        p = dummy;
        for(int i = 0; i < left-1; i++){
            p = p->next;
        }
        ListNode* b = p->next;
        p->next = nullptr;

        b = reverseN(b);

        p = dummy; //找第一部分的斷點
        while(p->next !=nullptr){
            p = p->next;
        }
        p->next = b;
        while(p->next != nullptr){
            p = p->next;
        }
        p->next = c;

        return dummy->next;// 怕head也被改到



    }
    ListNode* reverseN(ListNode* head){
        ListNode* previous = nullptr;
        ListNode* current = head;
        ListNode* precede = current->next;

        while(precede != nullptr){
            current->next = previous;
            previous = current;
            current = precede;
            precede = precede->next;
        }
        current->next = previous;
        head = current;

        return head;
    }
};

/*
解題思路：
此題需用到 反轉前n個node的技巧 結合 反轉某段區間的技巧兩段程式碼
1. recursion:  tc: o(n) sc: o(n)
2. iterative:  tc: o(n) sc: o(1) 
iterative: 本题的基本思路
我们需要将原列表拆分为三部分。然后对中间一部分进行链表反转操作（参考 206.Reverse-Linked-List），最后将三部分拼接起来。
需要注意的是left和right可能很极限，也就是说原题可能本质上是反转整个链表。所以方便的处理方法是前面添加一个dummy节点，
末尾也虚拟地认为有一个NULL节点。这样我们就一定能够把整个链表分为实实在在的三部分。然后应用上述的算法。

另外注意，所谓的将链表拆违三部分，并不是找到每一部分的首尾就完了，还要把尾节点的next置为NULL，
这样才能形成一个单独的链表。否则可能会有各种意想不到的bug。
*/
