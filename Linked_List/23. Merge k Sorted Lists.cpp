/*
23. Merge k Sorted Lists
*/




//此題想要你合併k個list 且要按小排到大 list被包在一個vector裡面 所以擷取出來的值需做調整..

// 10/11 TC:O(nklgk) k為當前priority queue中的數量 SC:O(k)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        auto comp = []( ListNode* a, ListNode* b){
            if(a->val != b->val)
                return a->val > b->val;
            else return a > b;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);

        for(auto list:lists){
            for(ListNode* p = list; p != NULL; p=p->next){
                pq.push(p);
            }
        }

        while(!pq.empty()){
            p->next = pq.top();
            pq.pop();
            p = p->next;
        }

        return dummy->next;

    }
};

class Solution {
    //另一種寫法 慢慢丟 BFS方式處理
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        auto comp = []( ListNode* a, ListNode* b){
            if(a->val != b->val)
                return a->val > b->val;
            else return a > b;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq(comp);

        for(auto list:lists){
            if(list != NULL)
                pq.push(list);
        }

        while(!pq.empty()){
            ListNode* node = pq.top();
            pq.pop();
            p->next = node;
            if(node->next != NULL) pq.push(node->next);
            p = p->next;
        }

        return dummy->next;

    }
};
// Divide and Conquer TC:O(nklgk) SC:O(lgk)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists,0,lists.size()-1);
    }

    ListNode* merge(vector<ListNode*>& lists, int left, int right){
        if(left > right) return nullptr;
        if(left == right) return lists[left];
        if(left + 1 == right) return mergeTwoLists(lists[left],lists[right]);
        int mid = left+(right-left)/2;
        auto l1 = merge(lists,left,mid);
        auto l2 = merge(lists,mid+1,right);
        return mergeTwoLists(l1,l2);
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        
        while(l1 && l2){
            if(l1->val > l2->val){
                p->next = l2;
                p = p->next;
                l2 = l2->next;
            }
            else{
                p->next = l1;
                p = p->next;
                l1 = l1->next;
            }
        }
        if(l1){
            p->next = l1;
        }
        if(l2){
            p->next = l2;
        }

        return dummy->next;
    }
};
// from la大 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;
        priority_queue<ListNode*, vector<ListNode*>, function<bool(ListNode*, ListNode*)> > pq([](ListNode* a,ListNode* b) 
        { return a->val > b->val; });
        //因為傳進來的會是位址 不能用原本的比較器比較 要比較的應該是他們的val
        
        //使用lamda函數 function bool代表函式主體會return的data type 裡面兩項為參數的data type

        for(auto head:lists){
            if(head!=nullptr){
                pq.push(head);//會按照大小排好
            }
        }
        while(!pq.empty()){
            ListNode* node = pq.top();
            pq.pop();
            p->next = node;
            if(node->next != nullptr) pq.push(node->next);
            p = p->next;
        }
        return dummy->next;
    }
};
/*
解題思路
此題屬於雙指針結合linked list題 因為此題需合併k個list 可以用priority queue去做排序
1.創立一個新list來放解答
2.將priority queue裡面的答案一一pop出來 放入解答裡 pq的答案需是由小而大 需要自定義 因為list被包在一個vector裡面 所以擷取出來的值需做調整..
*/
