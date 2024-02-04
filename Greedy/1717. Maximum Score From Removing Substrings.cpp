/*
1717. Maximum Score From Removing Substrings
*/

// 純Greedy 直接加入過程中檢查 TC:O(2*n) SC:O(n)
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        if(x < y){
            reverse(s.begin(), s.end());
            swap(x,y);
        }

        int res = 0;
        string t;
        for(auto ch : s){
            t.push_back(ch);
            if(t.size() >= 2 && t.substr(t.size()-2) == "ab"){
                res += x;
                t.pop_back();
                t.pop_back();
            }
        }

        string w;
        for(auto ch : t){
            w.push_back(ch);
            if(w.size() >= 2 && w.substr(w.size()-2) == "ba"){
                res += y;
                w.pop_back();
                w.pop_back();
            }
        }

        return res;
    }
};
// Stack TC:O(n^2) SC:O(n) 免強能過
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int n = s.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            int j = i;
            string temp;
            while(j < n && s[j] == 'a' || s[j] == 'b'){
                temp += s[j];
                j++;
            }
            if(!temp.empty()){
                res += helper(x,y,temp);
            }
            i = j;
        }

        return res;
    }

    int helper(int x, int y, string& str){
        int maxVal = 0;
        int n = str.size();
        // ab為主
        if(x > y){
            stack<char> stack; 
            for(int i = 0; i < n; i++){
                if(str[i] == 'a'){
                    stack.push('a');
                }
                else {
                    if(!stack.empty() && stack.top() == 'a'){
                        maxVal += x;
                        stack.pop();
                    }
                    else stack.push('b');
                }
            }

            int counta = 0;
            int countb = 0;
            while(!stack.empty()){
                // assume ch1 = b
                if(stack.top() == 'a') counta += 1;
                else countb += 1;
                stack.pop();
            }
            maxVal += min(counta,countb) * y;
        }

        else if(x <= y){
            stack<char> stack; 
            for(int i = 0; i < n; i++){
                if(str[i] == 'b'){
                    stack.push('b');
                }
                else {
                    if(!stack.empty() && stack.top() == 'b'){
                        maxVal += y;
                        stack.pop();
                    }
                    else stack.push('a');
                }
            }
            int counta = 0;
            int countb = 0;
            while(!stack.empty()){
                // assume ch1 = b
                if(stack.top() == 'a') counta += 1;
                else countb += 1;
                stack.pop();
            }
            maxVal += min(counta,countb) * x;
        }
        return maxVal;
    }
};

/*
這題要問說能夠ab or ba一組將他們刪除然後獲取分數 x or y 問說要怎麼貪心的刪除可以最高分
abba -> ba + ab
baab -> ba + ab
baba -> ab + ba or ba + ba看是ab大還是ba大 如果ab大就會想找他
abab -> ba + ab or ab + ab 看是ab大還是ba大
bbaa-> ba + ba
aabb-> ab + ab 這個也行
我的想法是切割字串 從a or b 開始一直到沒有出現a or b為止 代表除了aa bb ba ab a b之類的其他都不裝入
bababa -> 2*ab + ba
bbbbbbbaba

stack : b b b a a 
*/
