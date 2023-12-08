/*
1209. Remove All Adjacent Duplicates in String II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string removeDuplicates(string s, int k) {

        stack<pair<char,int>> stack;
        for(auto ch:s){
            if(!stack.empty() && ch == stack.top().first){
                stack.push({ch,stack.top().second+1});
            }
            else if(stack.empty() || ch != stack.top().first){
                stack.push({ch,1});
            }

            if(!stack.empty() && stack.top().second == k){
                for(int i = 0; i < k; i++){
                    stack.pop();
                }
            }
        }

        string res = "";
        while(!stack.empty()){
            res.push_back(stack.top().first);
            stack.pop();
        }

        reverse(res.begin(), res.end());
        

        return res;
    }
};

/*
此題給你一數字k 當字串內連續的字母長度達到此字串就要消除 不斷這樣做最後剩下的字串為？

*/
