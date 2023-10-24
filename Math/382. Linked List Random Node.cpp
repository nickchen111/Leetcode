/*
382. Linked List Random Node
*/

// TC:O(n) SC:O(1)
class Solution {
    ListNode* node;
public:
    Solution(ListNode* head) {
        node = head;
    }
    
    int getRandom() {
        ListNode* h = node;
        int k = 0;
        int x = 0;
        
        while(h!= NULL){
            k++;
            int r = random()%k;
            //必須設為0 才會在第一次的時候百分之百 之後都會是1/k的機率被取代 
            if(r == 0){
                x = h->val;
            }
            h = h->next;
        }

        return x;
    }
};

/*
隨機抽取一個數的題目從array 轉成 linked list該怎麼做 ->resouvior sampling
每次多一個數就可以隨機從現有的數字中抽出一個出來的演算法
int x = a;
int x = 1/2 x  1/2 b -> 1/2 a  1/2 b
int x = 2/3 x  1/3 c -> 1/3 a 1/3 b 1/3 c

*/
