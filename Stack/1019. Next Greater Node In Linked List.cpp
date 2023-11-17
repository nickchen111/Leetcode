/*
1019. Next Greater Node In Linked List
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        stack<pair<int,int>> stack; // value idx
        vector<int> nextGreater;
        int i =0;
        while(head != NULL){
            while(!stack.empty() && stack.top().first < head->val){
                nextGreater[stack.top().second] = head->val;
                stack.pop();
            }
            stack.push({head->val,i});
            i++;
            nextGreater.push_back(0);
            head=head->next;
        }

        return nextGreater;
    }
};
