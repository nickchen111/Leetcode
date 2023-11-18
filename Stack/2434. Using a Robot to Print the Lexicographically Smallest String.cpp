/*
2434. Using a Robot to Print the Lexicographically Smallest String
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string robotWithString(string s) {
        //Greedy + stack 希望湊出字典序最小的序列
        int n = s.size();
        vector<int> sufSmallest(n);
        char curSmall = 'z'+1;
        for(int i= n-1; i>=0; i--){
            curSmall = min(curSmall,s[i]);
            sufSmallest[i]=curSmall;
        }

        string res;
        stack<char> stack;
        int i = 0;
        while(i < n){
            if(stack.empty() || sufSmallest[i] < stack.top()){
                stack.push(s[i]);
                i++;
            }
            else {
                res+=stack.top();
                stack.pop();
            }
        }
        while(!stack.empty()){
            res+=stack.top();
            stack.pop();
        }

        return res;

    }
};
