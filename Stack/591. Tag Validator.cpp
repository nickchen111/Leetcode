/*
591. Tag Validator
*/

// TC:O(n) SC:O(k)
class Solution {
public:
    bool isValid(string code) {
        stack<string> stack;
        int i = 0;
        bool ever = 0; //因為頭必須要是<DIV>不是的話後面就都是false
        while(i <code.size()){
            //從長開始判斷
            if(i+8<code.size() && code.substr(i,9) == "<![CDATA["){
                i+=9;
                while(i+2 < code.size() && code.substr(i,3) != "]]>"){
                    i++;
                }
                if(i+2 == code.size()) return false;
                i+=3;
            }
            else if(i+1 < code.size() && code.substr(i,2) == "</"){
                i+=2;
                int j = i;
                while(i < code.size() && code[i] != '>') i++;
                if(i == code.size()) return false;
                string tagname = code.substr(j,i-j);
                if(stack.empty() || stack.top() != tagname) return false;
                stack.pop();
                i++;
                //尾巴也是必須在最後 當然中間可能包含很多頭尾 但在最後的最後尾巴去掉後stack必為空
                if(stack.empty() && i != code.size()) return false;
            }
            else if(code[i] == '<'){
                i++;
                int j=i;
                while(i<code.size() && code[i] != '>') i++;
                if(i == code.size()) return false;
                string tagname = code.substr(j,i-j);
                if(!isvalid(tagname)) return false;
                //判斷找到的頭是否為第一個
                if(ever == 0 && j != 1) return false;
                else ever = 1;
                stack.push(tagname);
                i++;
            }
            else i++;//既不是頭也不是尾的一些字元
        }

        if(!stack.empty()) return false;
        if(ever == 0) return false;

        return true;
    }
    bool isvalid(string tagname){
        if(tagname.size() > 9 || tagname.size() < 1) return false;
        for(auto ch:tagname){
            if(ch > 'Z' || ch < 'A') return false;
        }
        return true;
    }
};

/*
此題就是要處理字符串的三種狀況
1.頭必須是<DIV> 尾必須是</DIV> 包含的字母必須是大寫字母並且長度介於1~9
2. <![CDATA[ 當頭可以容納任何東西 以]]>結尾
3. 其餘字符隨意可直接略過
*/
