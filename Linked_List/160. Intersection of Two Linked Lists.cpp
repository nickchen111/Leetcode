/*
160. Intersection of Two Linked Lists
*/



// Two pointer TC:O(n+k) n為headA長度 k為headB長度 SC:O(1)
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while(p1 != p2){ //想找到相同的點 如果兩個都找遍了都等於nullptr也會跳出while loop
            if(p1 == nullptr) p1 = headB;
            else p1 = p1->next;
            if(p2 == nullptr) p2 = headA;
            else p2 = p2->next;

        }
        return p1;
    }
};

// hash table TC:O(m+n) SC:O(m)
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        unordered_map<ListNode*, int> m;
        while(p1 != nullptr){
            m[p1]++;
            p1 = p1->next;
        }
        while(p2 != nullptr){
            if(m[p2] > 0){
                return p2;
            }
            p2 = p2->next;
        }
        return nullptr;
    }
};


/*
此題也可以使用hash table
解題思路
1.使用雙指針去指向各linked list 兩邊開始往前走找交點
2.如果長度不一的情況下只要互相走對方 長度就會一致了 此時相同的點就會是交點
*/
