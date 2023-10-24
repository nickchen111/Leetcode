/*
234. Palindrome Linked List
*/

class Solution {
    //快慢指針
public:
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast != nullptr && fast->next != nullptr){ //不能只列fast != nullptr 因為fast一次走兩步怕會到怪的地方
            slow = slow->next;
            fast = fast->next->next;
        }
        if(fast != nullptr){ //奇數的情況
            slow = slow->next;
        }

        ListNode* left = head;
        ListNode* right = reverse(slow);
        while(right != nullptr){
            if(left->val != right->val){
                return false;
            }
            left = left->next;
            right = right->next;
        }

        return true;
    }

    ListNode* reverse(ListNode* node){
        ListNode* previous = nullptr;
        ListNode* current = node;
        ListNode* next;
        while(current != nullptr){
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        return previous;
    }
};

class Solution {
    //後序遍歷
public:
    ListNode* left;
    bool isPalindrome(ListNode* head) {
        left = head;

        return traverse(head);
    }

    bool traverse(ListNode* right){
        if(right == nullptr) return true;

        bool res = traverse(right->next);
        //後序遍歷位置

        res = res && (left->val == right->val);
        left = left->next;
        return res;
    }
};

/*
解題思路：
判斷linked list是否是回文串
一般我們判斷回文串會是用雙指針從兩邊往中間集中判斷 但是linked list沒辦法立刻判斷尾巴的位置 所以：
1. 利用後序遍歷的方式做遞迴 判斷前後值是否相同 tc: o(n) sc: o(n)
2. 利用快慢指針 去找到linked list中點 但這招需要判斷串是奇數還是偶數 如果是奇數 slow還要再往後走一步
第二個方法因為不用遞歸所以可以減少空間複雜度 
tc: o(n) sc: o(1)

如果題目要求鍊錶的結構要恢復原樣 在return以前加上 p.next = reverse(q); p要再自己去遍歷一下即可知道

*/
