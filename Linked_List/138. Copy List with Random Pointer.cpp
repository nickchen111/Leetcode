/*
138. Copy List with Random Pointer
*/


//TC:O(n) SC:O(n)
class Solution {
    unordered_map<Node*, Node*> clone; //分別存舊跟新結點互相對映
public:
    Node* copyRandomList(Node* head) {
        //two pass
        //第一次先將節點用map記錄起來
        for(Node* p = head; p!=NULL; p = p->next){
            clone[p] = new Node(p->val);
        }

        //開始連結
        for(Node* p = head; p!=NULL; p=p->next){
            //兩件事情 將新節點的next連結在一起 將新節點的random也設定好
            clone[p]->next = clone[p->next];
            clone[p]->random = clone[p->random];
        }

        return clone[head];
    }
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
