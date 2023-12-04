/*
2264. Largest 3-Same-Digit Number in String
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    string largestGoodInteger(string num) {
        string res = "";
        int n = num.size();
        for(int i = 0; i < n-2; i++){
            string cur = num.substr(i,3);
            if(cur[0] == cur[1] && cur[1] == cur[2]){
                if(res == "" || stoi(cur) > stoi(res)){
                    res = cur;
                }
            }
        }

        return res;
    }
};

/*
此題限制 
1.必須是長度為3
2.必須是相同數字
想法是每次都取三個數 取完跟目前的比大小
*/
