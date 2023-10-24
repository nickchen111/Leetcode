/*
21. Merge Two Sorted Lists
*/


 //Definition for singly-linked list.
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode(-1); //建立虛擬頭節點
        ListNode* p = dummy;
        ListNode* p1 = list1;
        ListNode* p2 = list2;
        while(p1 != nullptr && p2 != nullptr){
            if(p1->val < p2->val){
                p->next = p1;
                p1 = p1->next;
            }
            else {
                p->next = p2;
                p2 = p2->next;
            }
            p = p->next;// p 指针不断前进
        }
        if(p1 != nullptr){
            p->next = p1; //極端情況
        }
        if(p2 != nullptr){
            p->next = p2;//極端情況
        }
        return dummy->next;
    }
};

/*
解題思路：
1.首先創造一個虛擬頭節點 以防止向空指針的麻煩情況 與一個p指標去指向他
2.設立p1 p2指標分別指向兩個list
3.去比p1 p2指向的值大小 小的就讓他加入p指標內
4.注意極端情況 如果p1 or p2先被排完的話 p->next就直接指向剩餘的一方

linked list 基本概念:
= 操作符在 C++ 中对指针来说是将一个指针指向另一个指针的内容，而不是复制链表的内容。
*/

/*
chatgpt給的與86題不同操作的元因

不需要在 p1 和 p2 的操作中执行 ListNode* temp = p->next; p->next = nullptr; p = temp; 这样的操作的原因是，
这里的 p1 和 p2 指针在每一步的操作中都是将节点链接到新链表上，并且不会改变原始链表的结构。在这种情况下，将 p1 或 p2 的节点链接到新链表中后，它们本身不再维持原始链表的连接，因此不会出现“悬挂”节点。

这种情况与之前提到的代码不同，之前的代码是将一个链表分割成两个链表，需要断开原链表的连接，因此需要用额外的指针来保存下一个节点的引用，然后断开当前节点的连接。

在这个问题中，p1 和 p2 实际上只是作为指针，指向原始链表中的节点，并将它们链接到新链表中。它们在新链表中的每个节点都会被链接到，因此不需要进行类似的断开连接操作。

我的理解是因為這題的p1 p2都是跑去相同的linked list上 原始list跟彼此都還有連結 而86題的話會是跑到兩個list上 所以需斷開鏈結 用temp去紀錄p->next 在用心的p去指向他
*/


/*
10/11
其實86題會需要額外的操作是因為擔心p1 p2的後面接得不乾淨 然後此指針會不斷被p1 p2給指向 如果此指針想往下一步走 那就先需要為了p1 p2 將他後面的東西假裝斷開(先用一個temp儲存) 在自個兒接上
但其實也可以先不管他 順順的寫 因為終究 p1會連接到p2的頭 到時候直接處理p2尾巴為ＮＵＬＬ即可
*/
