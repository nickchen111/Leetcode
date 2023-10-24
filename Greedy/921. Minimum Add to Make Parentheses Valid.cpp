/*
921. Minimum Add to Make Parentheses Valid
*/

// greedy TC:O(n) SC:O(1)
class Solution {
public:
    int minAddToMakeValid(string s) {
        int count = 0;
        int res = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                count++;
            }
            else{
                count--;
            }
            while(count < 0){
                res++;
                count++;
            }
        }

        if(count >0){
            res+=count;
        }

        return res;
    }
};
/*
跟1541類似的概念
不過這題是完全符合括號規則來做
*/
