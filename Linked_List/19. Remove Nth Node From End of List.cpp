/*
19. Remove Nth Node From End of List
*/

// 11/1 TC:O(n) SC:O(1)
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //倒數第n個也就是在多走n步就會出界 要找到倒數n+1個
        //這題就是讓p1跟p2永遠差n的距離 當p1到頭 p2就會是倒數n個
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* p1 = dummy;
        for(int i = 0; i<n+1; i++){
            p1 = p1->next;
        }
        ListNode* p2 = dummy;
        while(p1 != NULL){
            p1 = p1->next;
            p2 = p2->next;
        }

        //此時p2就會是倒數n+1個
        p2->next = p2->next->next;
        return dummy->next;
    }
};

// 此題是想讓你將一串linked list裡面的倒數第n個元素給刪掉
//TC:O(n) SC:O(1)
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
