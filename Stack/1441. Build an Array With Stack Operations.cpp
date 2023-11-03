/*
1441. Build an Array With Stack Operations
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> res;
        stack<string> s;
        int i = 1;
        int j = 0;
        while(i <= n){
            if(i == target[j]){
                i++;
                j++;
                s.push("Push");
                if(j == target.size()) break;
            }
            else if(i != target[j]){
                i++;
                s.push("Push");
                s.push("Pop");
            }

        }

        while(!s.empty()){
            res.insert(res.begin(), s.top());
            s.pop();
        }

        return res;

    }
};
