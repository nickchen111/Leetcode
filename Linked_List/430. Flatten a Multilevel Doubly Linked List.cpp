/*
430. Flatten a Multilevel Doubly Linked List
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    Node* flatten(Node* head) {
        //此題要你把node的child 改成next 並且優先走child 然後將child的尾接上next頭
        // h + h(child) + h(next)
        DFS(head);
        return head;
    }
    Node* DFS(Node* h){
        if(h == NULL) return NULL;
        Node* child = h->child;
        Node* next = h->next;
        h->child = NULL;
        if(child && next){
            Node* childEnd = DFS(child);
            Node* nextEnd = DFS(next);

            h->next = child;
            child->prev = h;

            childEnd->next = next;
            next->prev = childEnd;
            return nextEnd;//返回一個練表lu直後的尾節點
        }
        else if(child && !next){
            Node* childEnd = DFS(child);
            h->next = child;
            child->prev = h;

            return childEnd;

        }
        else if(!child && next){
            Node* nextEnd = DFS(next);
           
            return nextEnd;
        }
        else{
            return h;
        }
    }
};
