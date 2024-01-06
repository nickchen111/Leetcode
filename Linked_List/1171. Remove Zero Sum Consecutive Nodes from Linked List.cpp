/*
1171. Remove Zero Sum Consecutive Nodes from Linked List
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int sum = 0;
        unordered_map<int, ListNode*> map;
        for(ListNode* i = dummy; i; i = i->next){
            map[sum+=i->val] = i;
        }
        sum = 0;
        for(ListNode* i = dummy; i; i = i->next){
            i->next = map[sum+=i->val]->next;
        }

        return dummy->next;
    }
};

/*
此題問將Linked List內加總起來會變成0的元素刪掉 重新拼接出來的LInked List 不能有相加為0的狀況 
這題一開始的想法就是先想轉成陣列要怎麼做 然後會想到用map記錄每次相加結果 當相加結果重複就代表那一區間的數值都要刪除
但事實做起來邏輯還是不太對一些 最理想的做法是將各種可能的和出現的最後一次的位置確定好 在第二次遍歷過程中去構造LInked List自然就會跳轉到後面 
並且也不用擔心跳轉過去和的狀態是不對的畢竟跳轉過去忽略的那段總和會是0 有加入跟沒加入一樣 不會影響後續判斷
*/
