/*
2058. Find the Minimum and Maximum Number of Nodes Between Critical Points
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int minPos = -1;
        int maxPos = -1;
        int minDis = INT_MAX;
        int maxDis = INT_MIN;
        int prev = -1;
        int count = -1;
        while(head->next != NULL){
            count += 1;
            if((head->val > prev) && (head->val > head->next->val) && prev != -1){
                if(minPos == -1){
                    minPos = count;
                    maxPos = count;
                }
                else {
                    minDis = min(minDis, count-maxPos);
                    maxPos = count;
                    maxDis = maxPos - minPos;
                }
            }
            else if((head->val < prev) && (head->val < head->next->val) && prev != -1){
                if(minPos == -1){
                    minPos = count;
                    maxPos = count;
                }
                else {
                    minDis = min(minDis, count-maxPos);
                    maxPos = count;
                    maxDis = maxPos - minPos;
                }
            }
            prev = head->val;
            head = head->next;
        }

        if(minDis == INT_MAX) return {-1,-1};
        else return {minDis, maxDis};
    }
};
