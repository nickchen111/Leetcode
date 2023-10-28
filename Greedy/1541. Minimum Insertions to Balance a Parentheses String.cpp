/*
1541. Minimum Insertions to Balance a Parentheses String
*/

//這個寫法更好一點 可以應對如果變成 一個左括弧需要三個右括號的狀況 if(count%3 != 0)...res+=(count%3); count-=(count%3);
class Solution {
public:
    int minInsertions(string s) {
        int count = 0;
        int res = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                count+=2;
                //一個左括號需要兩個右括號 如果這時count 為奇數代表還缺一個右括號的時候就接到另一個左括號了
                if(count%2 == 1){
                    res+=1;
                    count-=1;
                }
            }
            else if(s[i] == ')'){
                count-=1;
                if(count == -1){
                    res+=1;
                    count+=2;
                }
            }
        }

        //缺右括號
        if(count > 0){
            res+=count;
        }

        return res;
    }
};

//greedy TC:O(n) SC:O(1)
class Solution {
    //greedy
public:
    int minInsertions(string s) {
        int count = 0;
        int res = 0;//操作增加的次數
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                count++;
            }
            else{
                if(i+1 < s.size() && s[i+1] == ')'){
                    count--;
                    i++;//因為這裡有刻意多比較了一個
                }
                else{
                    res++;
                    count--;
                }
            }
            //如果右括號太多了
            if(count < 0){
                res++;//插入一個左括號
                count++;
            }
        }
        if(count > 0){
            res+=2*count;
        }

        return res;
    }
};

/*
括號題要想到兩個方法
1. stack
2. greedy->count: unmatched left parentheses
a. must two consecutive ) to cancel one ()\
b. at the end ret+=2*count; 因為可能有一些剩下的左括號
*/
