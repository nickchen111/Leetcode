/*
25. Reverse Nodes in k-Group
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
    //iterative
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == nullptr) return nullptr;

        vector<ListNode*> heads; //紀錄每一段的頭
        ListNode* p = head; //指針去搜尋每段的頭
        int flag = 1;// 用於標記是否有足夠的 k 個元素


        //開始去判斷需要幾次翻轉
        while(p){
            heads.push_back(p);//加入每段的頭節點 不足k個的也會被加進去
            for(int i = 0; i < k-1; i++){// 移動指針至每一段的尾節點，確認是否存在這一段
                if(p->next){
                    p = p->next;
                }
                else flag = 0;// 如果不滿足 k 個元素，將 flag 設為 0
            }
            ListNode* next = p->next;
            p->next = nullptr;//斷開
            p =next;
        }
        for(int i = 0; i < heads.size(); i++){
            if(flag != 0 || i != heads.size()-1){ // if(flag == 0 && i == heads.size()-1 ) continue; //不用反轉 這樣寫更直觀
                heads[i] = reverse(heads[i]);//數組紀錄翻轉後的頭節點
            }
        }
        for(int i=0; i < heads.size()-1; i++){//五個頭只要做四次的概念 like 4 edge
            ListNode* h = heads[i];
            while(h->next) h = h->next;
            h->next = heads[i+1];
        }
        
        return heads[0];
    }

    ListNode* reverse(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next;
        while(curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};

class Solution {
// recursion
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == nullptr) return nullptr; //沒東西可轉

        ListNode* left = head;
        ListNode* right = head;// 兩指針去指向著要翻轉的k個node
        
        for(int i = 0; i < k; i++){//左閉右開的方式
            if(right == nullptr) return head;
            right = right->next;
        }

        ListNode* newhead = reverse(left, right); //也可以選擇把它斷開在接上的方式(iterative) 這樣就不是左閉右開分法
        
        left->next = reverseKGroup(right, k);//recursion

        return newhead;
    }

    ListNode* reverse(ListNode* left, ListNode* right){
        ListNode* previous = nullptr;
        ListNode* current = left;
        ListNode* next;
        while(current != right){
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        return previous;
    }
};

/*
此題是k個一組翻轉鍊錶
所以也需考慮到剛開始分配or分配到後來如果不滿足k個的base case 不足的部分就不用翻轉了
利用遞歸的方式分段去翻轉 
1. 先用兩個指針開始劃分要分段的位置 採用左閉右開的方式 這樣終止條件會比較clear
2. 多建立一個函式對包覆著的區間做reverse
3. 然後讓原本的left->next去指向下一個準備分段的recursion 函式(left指向的地方不會跑掉) 
 tc: o(n) sc: o(1)

利用iterative方式：
概念是 我想去紀錄每一段的頭節點 並且去翻轉每一段 過程中每一段的頭再去接上下一段
如果最後一組不滿足 ｋ個的話 此條件要再多做處理
tc: o(n) sc: o(n)
*/
