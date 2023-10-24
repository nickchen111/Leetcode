/*
86. Partition List
*/

// TC: O(N) SC: O(N)
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
       ListNode* dummy1 = new  ListNode(-1);
       ListNode* dummy2 = new  ListNode(-1);
       ListNode* p1 = dummy1;
       ListNode* p2 = dummy2;
       ListNode* p =head;
       while(p != nullptr){
           if(p->val < x){
               p1->next = new ListNode(p->val);//創建一個新的listnode 就不會有指針不知道指到哪的問題 但需要耗費比較多空間
               p1 = p1->next;//小的list
           }
           else{
               p2->next = new ListNode(p->val);
               p2 = p2->next;//大的list
           }
           p = p->next;
       }
       p1->next = dummy2->next;

       return dummy1->next;
    }
};

/*
解題思路
1.創建兩個虛擬頭節點去存放大於等於 以及小於的情況
2. 將head內數字與 x比較大小
3.比較完之後將兩個linked list頭尾相接起來 注意不要接到虛擬頭節點的部分
*/


// 10/11
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        //改成直接從head自己出發 不用指針指向他 反正最後答案也不在乎head指向原liust的哪
        ListNode* dummy1 = new ListNode(0);
        ListNode* dummy2 = new ListNode(0);
        ListNode* p1 = dummy1;
        ListNode* p2 = dummy2;
        while(head != NULL){
            if(head->val >= x){
                p2->next = head;
                p2 = p2->next;
                head = head->next;
            }

            else {
                p1->next = head;
                p1 = p1->next;
                head = head->next;
            }
        }

        p1->next = dummy2->next;
        p2->next = NULL;
        return dummy1->next;
    }
};


//不用new 新空間的寫法 但須額外處理
class Solution {
public:
ListNode* partition(ListNode* head, int x) {
    // 存放小于 x 的链表的虚拟头结点
    ListNode* dummy1 = new ListNode(-1);
    // 存放大于等于 x 的链表的虚拟头结点
    ListNode* dummy2 = new ListNode(-1);
    // p1, p2 指针负责生成结果链表
    ListNode* p1 = dummy1, * p2 = dummy2;
    // p 负责遍历原链表，类似合并两个有序链表的逻辑
    // 这里是将一个链表分解成两个链表
    ListNode* p = head;
    while (p != nullptr) {
        if (p->val >= x) {
            p2->next = p;
            p2 = p2->next;
        } else {
            p1->next = p;
            p1 = p1->next;
        }
        // 断开原链表中的每个节点的 next 指针
        ListNode* temp = p->next;
        p->next = nullptr;
        p = temp;
    }
    // 连接两个链表
    p1->next = dummy2->next;

    return dummy1->next;
}
};

/*
10/11
其實86題會需要額外的操作是因為擔心p1 p2的後面接得不乾淨 然後此指針會不斷被p1 p2給指向 如果此指針想往下一步走 那就先需要為了p1 p2 將他後面的東西假裝斷開(先用一個temp儲存) 在自個兒接上
但其實也可以先不管他 順順的寫 因為終究 p1會連接到p2的頭 到時候直接處理p2尾巴為ＮＵＬＬ即可
*/
