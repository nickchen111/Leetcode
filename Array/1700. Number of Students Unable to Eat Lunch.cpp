/*
1700. Number of Students Unable to Eat Lunch
*/


// TC:O(n*k) k 為會經過的回合數 SC:O(n)
class Solution {
public:
    int countStudents(vector<int>& students, vector<int>& sandwiches) {
        queue<int> q;
        stack<int> stack;
        for(auto s : students){
            q.push(s);
        }
        for(int i = sandwiches.size()-1; i >= 0; i--){
            stack.push(sandwiches[i]);
        }

        vector<int> tmp;
        while(true){
            int sz = q.size();
            while(!q.empty()){
                if(q.front() == stack.top()){
                    q.pop();
                    stack.pop();
                }
                else {
                    tmp.push_back(q.front());
                    q.pop();
                }
            }
            if(tmp.size() == sz){
                break;
            }
            else if (tmp.size() == 0) break;
            else {
                for(auto x : tmp){
                    q.push(x);
                }
                tmp.clear();
            }
        }

        return (int)tmp.size();
    }
};
