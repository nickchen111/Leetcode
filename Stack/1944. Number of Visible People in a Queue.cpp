/*
1944. Number of Visible People in a Queue
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        //維護一個從右往左的遞減序列
        int n = heights.size();
        vector<int> res(n);
        stack<int> stack;
        for(int i=n-1; i>=0; i--){
            int count = 0;
            while(!stack.empty() && heights[stack.top()] < heights[i]){
                count++;
                stack.pop();
            } 
            if(!stack.empty()) count++;
            res[i]=count;
            stack.push(i);
        }
        
        return res;
    }
};
